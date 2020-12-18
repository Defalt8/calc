#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <calc.h>

const int 
    CALC_VERSION_MAJOR = __CALC_VERSION_MAJOR, 
    CALC_VERSION_MINOR = __CALC_VERSION_MINOR, 
    CALC_VERSION_PATCH = __CALC_VERSION_PATCH;
const double Nan = nan("");

typedef enum _Mode { MD_None, MD_Value, MD_Operator } Mode; 

double operate(double left, double right, char operator)
{
    switch (operator)
    {
        case '+': return (left + right);
        case '-': return (left - right);
        case '*': return (left * right);
        case '/': return (left / right);
        case '%': return fmod(left, right);
        case '^': return pow(left, right);
        default: return Nan;
    }
}

double calcEvaluate(const char* expression)
{
    size_t len, last_i = 0;
    if(!expression || (len = strlen(expression)) == 0) return 0.0;
    double result = 0.0, operand = 0.0;
    char last_operator = '\0';
    int white_space = 0;
    Mode mode = MD_None;
    for(int i=0; i<=len; ++i)
    {
        if(i == len)
        {
            switch (mode)
            {
                case MD_None: return result;
                case MD_Operator: return Nan;
                case MD_Value:
                    switch(last_operator)
                    {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '%':
                        case '^':
                            result = operate(result, operand, last_operator);
                            operand = 0.0;
                            break;
                        default:
                            result = operand;
                            break;
                    }
                    break;
            }
            return result;
        }
        const char c = expression[i];
        switch(c)
        {
            case ' ': case '\t': break;
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            case '.':
                switch (mode)
                {
                    case MD_None:
                    case MD_Operator:
                        operand = atof(&expression[i]);
                        last_i = i;
                        mode = MD_Value;
                        break;
                    case MD_Value:
                        if(white_space) return Nan;
                        continue;
                }
                break;
            case '+': case '-': case '*': case '/': case '%': case '^':
                switch (mode)
                {
                    case MD_None:
                        switch(c)
                        {
                            case '+': case '-':
                                last_operator = c;
                                break;
                            case '*': case '/': case '%': case '^':
                                return Nan;
                        }
                        mode = MD_Operator;
                        break;
                    case MD_Value:
                        switch(last_operator)
                        {
                            case '+': case '-':
                                switch(c)
                                {
                                    case '*': case '/': case '%': case '^':
                                        operand = calcEvaluate(&expression[last_i]);
                                        if(isnan(operand)) return Nan;
                                        result = operate(result, operand, last_operator);
                                        return result;
                                    default: break;
                                }
                            case '*': case '/': case '%':
                                switch(c)
                                {
                                    case '^':
                                        operand = calcEvaluate(&expression[last_i]);
                                        if(isnan(operand)) return Nan;
                                        result = operate(result, operand, last_operator);
                                        return result;
                                    default: break;
                                }
                            case '^':
                                result = operate(result, operand, last_operator);
                                operand = 0.0;
                                last_operator = c;
                                break;
                            default:
                                result = operand;
                                break;
                        }
                        last_operator = c;
                        mode = MD_Operator;
                        break;
                    case MD_Operator:
                        return Nan;
                }
                break;
            case'(':
                {
                    char buffer[256];
                    size_t j;
                    for(j=i+1; j<=len; ++j)
                        if(expression[j] == ')') break;;
                    if(j == len) return Nan;
                    const size_t sub_len = (j-(i+1));
                    strncpy(buffer, &expression[i+1], sub_len);
                    buffer[sub_len] = '\0';
                    operand = calcEvaluate(buffer);
                    last_i = i;
                    if(isnan(operand)) return Nan;
                    i = j;
                    mode = MD_Value;
                    continue;
                }
                break;
            default:
                return Nan;
        }
        switch(c)
        {
            case ' ': case '\t':
                white_space = 1;
                break;
            default:
                white_space = 0;
                break;
        }
    }
    return result;
}