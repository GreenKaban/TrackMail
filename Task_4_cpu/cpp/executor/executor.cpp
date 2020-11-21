#include "executor.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

Executor::Executor(Program *program) : Executor(program, nullptr) {}

Executor::Executor(Program* program, logger* log_)
{
    assert(program != nullptr);

    this->program = program;
    this->log_ = log_;

    checked_log(log_, LVL_DEBUG, "Executor: constructed");
}

void Executor::execute()
{
    checked_log(log_, LVL_DEBUG, "Executor: execute()");

    collect_marks();

    for (ulong i = 0; i < program->statements.size(); ++i)
    {
        Statement* statement = program->statements[i];
        switch (execute_statement(statement, i))
        {
            case ok:
                continue;
            case error_:
            {
                string message;
                if (statement->command == nullptr)
                    message = "Statement execution failed.";
                else
                    message = format(
                            "Statement execution failed at %d:%d, command %s",
                            statement->command->line,
                            statement->command->symbol,
                            statement->command->value.c_str());
                checked_log(log_, LVL_ERROR, message);
                ERROR_EXIT_JUST_MES(message.c_str(),
                        statement_execution_error);
            }
            case finish:
                return;
        }
    }
}

void Executor::collect_marks()
{
    for (ulong i = 0; i < program->statements.size(); ++i)
    {
        Statement* statement = program->statements[i];
        if (statement->command_type == mark)
        {
            Token* mark_token = statement->arguments[0]->token;
            if (mark_token->type != identifier)
            {
                string message = format("Invalid mark argument '%s' "
                        "at %d:%d. Expected identifier, got %d",
                        mark_token->value.c_str(),
                        mark_token->line, mark_token->symbol, mark_token->type);
                checked_log(log_, LVL_ERROR, message);
                ERROR_EXIT_JUST_MES(message.c_str(), invalid_mark);
            }
            if (marks.count(mark_token->value) > 0)
            {
                string message = format("Repeating marker '%s' at %d:%d",
                        mark_token->value.c_str(),
                        mark_token->line, mark_token->symbol);
                checked_log(log_, LVL_ERROR, message);
                ERROR_EXIT_JUST_MES(message.c_str(), invalid_mark);
            }
            marks[mark_token->value] = (uint)i;
        }
    }
}

StatementResult Executor::execute_statement(Statement* statement, ulong& i)
{
    {
        string message;
        if (statement->command == nullptr)
            message = format("Executor: execute_statement(). "
                             "command_type: %d",
                    statement->command_type);
        else
            message = format("Executor: execute_statement(). "
                             "%d:%d, command %s",
                    statement->command->line, statement->command->symbol,
                    statement->command->value.c_str());
        checked_log(log_, LVL_DEBUG_2, message);
    }

    switch (statement->command_type)
    {
        case invalid:
            return error_;
        case add:
        case sub:
        case mul:
        case CommandType::divide:
        case power:
        case mod:
        case CommandType::less:
        case more:
        case less_eq:
        case more_eq:
        case eq:
        case not_eq_:
            return execute_binary_command(statement->command_type);
        case sqrt_:
        {
            char value = stack_.top();
            stack_.pop();
            stack_.push((char)std::sqrt(value));
            return ok;
        }
        case not_:
        {
            char value = stack_.top();
            stack_.pop();
            stack_.push(!value);
            return ok;
        }
        case push:
            stack_.push(statement->arguments[0]->value);
            return ok;
        case dup:
            stack_.push(stack_.top());
            return ok;
        case put:
        {
            char index = statement->arguments[0]->value;
            assert(index >= 0 && index <= n_registers);
            registers[(uint)index] = stack_.top();
            stack_.pop();
            return ok;
        }
        case take:
        {
            char index = statement->arguments[0]->value;
            assert(index >= 0 && index <= n_registers);
            stack_.push(registers[(uint)index]);
            return ok;
        }
        case in:
        {
            int val;
            scanf("%d", &val);
            if (val < 0 || val > 255)
            {
                string message = format("Invalid input value: %d", val);
                checked_log(log_, LVL_ERROR, message);
                ERROR_EXIT_JUST_MES(message.c_str(),
                        statement_execution_error);
            }
            stack_.push((char)val);
            return ok;
        }
        case out:
            printf("%d", (signed char)stack_.top());
            stack_.pop();
            return ok;
        case out_char:
            printf("%c", stack_.top());
            stack_.pop();
            return ok;
        case CommandType::end:
            return finish;
        case mark:
            return ok;
        case goto_:
        case visit:
        {
            Token *mark_token = statement->arguments[0]->token;
            if (mark_token->type != identifier) {
                string message = format("Invalid mark argument '%s' "
                        "at %d:%d. Expected identifier, got %d",
                        mark_token->value.c_str(),
                        mark_token->line, mark_token->symbol,
                        mark_token->type);
                checked_log(log_, LVL_ERROR, message);
                ERROR_EXIT_JUST_MES(message.c_str(), invalid_mark);
            }
            if (marks.count(mark_token->value) <= 0) {
                string message = format("Undeclared marker '%s' at %d:%d",
                        mark_token->value.c_str(),
                        mark_token->line, mark_token->symbol);
                checked_log(log_, LVL_ERROR, message);
                ERROR_EXIT_JUST_MES(message.c_str(), invalid_mark);
            }
            if (statement->command_type == visit)
                back_positions.push((uint)i);
            i = marks[mark_token->value];
            return ok;
        }
        case back:
            i = back_positions.top();
            back_positions.pop();
            return ok;
    }
}

StatementResult Executor::execute_binary_command(CommandType command_type)
{
    char l, r;
    r = stack_.top();
    stack_.pop();
    l = stack_.top();
    stack_.pop();

    switch (command_type)
    {
        case add:
            stack_.push(l + r);
            return ok;
        case sub:
            stack_.push(l - r);
            return ok;
        case mul:
            stack_.push(l * r);
            return ok;
        case CommandType::divide:
            stack_.push(l / r);
            return ok;
        case power:
            stack_.push((char)std::pow(l, r));
            return ok;
        case mod:
            stack_.push(l % r);
            return ok;
        case CommandType::less:
            stack_.push(l < r);
            return ok;
        case more:
            stack_.push(l > r);
            return ok;
        case less_eq:
            stack_.push(l <= r);
            return ok;
        case more_eq:
            stack_.push(l >= r);
            return ok;
        case eq:
            stack_.push(l == r);
            return ok;
        case not_eq_:
            stack_.push(l != r);
            return ok;
        default:
            return error_;
    }
}
