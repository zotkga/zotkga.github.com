#include <stdio.h> // 메시지 입/출력
#include <stdlib.h> // 랜덤
#include <string.h> // 문자열 처리
#include <ctype.h> // 알파벳 확인

#define MAX_STACK_SIZE 100

// 스택 생성
typedef int element;
typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s) {
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s) {
    return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 오버플로\n");
        return;
    } else {
        s->stack[++(s->top)] = item;
    }
}

// 삭제 함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 언더플로\n");
        return;
    } else {
        return s->stack[(s->top)--];
    }
}

// 피크 함수
element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        return;
    } else {
        return s->stack[s->top];
    }
}

// 우선순위
int prec(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '=':           return 1;
    case '+': case '-': return 2;
    case '*': case '/': return 3;
    case '^':           return 4;
    default:            return -1;
    }
}

// 중위표기식 -> 후위표기식 변환 함수
void infix_to_postfix(char exp[], char cexp[]) {
    int i, j = 0;
    char ch, ch2;
    char top_op;
    int len = (int)strlen(exp);

    StackType s;
    init_stack(&s);

    for (i = 0; i < len; i++) {
        ch = exp[i];
        ch2 = exp[i + 1];

        switch (ch) {
        case '+': case '-': case '*': case '/': case '^': case '=':
            while (
                !is_empty(&s) 
                && (prec(ch) <= prec(peek(&s)))
                ) 
            {
                cexp[j++] = pop(&s);
            }
            push(&s, ch);
            break;

        case '(':
            push(&s, ch);
            break;
        
        case ')':
            top_op = pop(&s);
            while (top_op != '(') {
                cexp[j++] = top_op;
                top_op = pop(&s);
            }
            break;

        default:
            cexp[j++] = ch;
            if (ch2 != '+' && ch2 != '-' && ch2 != '*' && ch2 != '/' && ch2 != '^' && ch2 != '=' && ch2 != '\0' &&
                ch2 != '(' && ch2 != ')') {
                cexp[j++] = ch2;
                i++;
            }
            break;
        }
    }

    while (!is_empty(&s)) {
        cexp[j++] = pop(&s);
    }
    cexp[j] = '\0';
}

#define MAX_EXPR_SIZE 100
#define MAX_HEARTS 5

// 랜덤 중위표기식 생성 함수
void generate_random_infix(char *exp, int expr_size) {
    const char *operators = "+-*/^()=";
    int len = 0; // 생성된 식의 길이
    int open_gwalho = 0; // 열린 괄호의 개수
    int equal_used = 0; // '=' 사용 횟수
    char next_char = 'a'; // 다음에 사용될 문자열
    int expect_operator = 0; // 연산자 생성

    while (len < expr_size - 1) {
        if (expect_operator == 1) {
            char op;
            do { // do-while문
                op = operators[rand() % strlen(operators)];
            } while (  
                (
                    op == '=' &&
                    (
                        equal_used != 0 || 
                        open_gwalho != 0
                    )
                )
                ||
                (
                    op == '(' &&
                    (
                        exp[len - 1] == ')' ||
                        isalpha(exp[len - 1])
                    )
                )
                ||
                (
                    op == ')' && 
                    (
                        strchr("+-*/^=(", exp[len - 1]) ||
                        open_gwalho < 1
                    )
                )
                ||
                (
                    op != '(' && 
                    strchr("+-*/^=(", exp[len - 1])
                )
            );
            // 선택 완료
            if ( op == '(' ) {
                open_gwalho++;
                expect_operator = 0;
            } 

            else if ( op == ')' ) {
                open_gwalho--;
                expect_operator = 1;
            } 

            else {
                if ( op == '=' ) {
                    equal_used = 1;
                }
                expect_operator = rand() % 3;
            }

            exp[len++] = op;

        }
        else {
            exp[len++] = next_char++;
            expect_operator = 1;
        }

        if (
                open_gwalho != 0 &&
                rand() % 4 == 0 &&
                !strchr("+-*/^=(", exp[len - 1]) &&
                len < expr_size - 1
            ) {
                exp[len++] = ')';
                open_gwalho--;
                expect_operator = 1;
        }
    }
    
    while (len > 0 && (strchr("+-*/^=(", exp[len - 1]))) {
        if (exp[len - 1] == '(') {
            open_gwalho--;
        }
        len--;
    }

    while (open_gwalho != 0) {
        exp[len++] = ')';
        open_gwalho--;
    }

    exp[len++] = '\0';
}

// 게임 시작 함수
void start_game() {
    int hearts = MAX_HEARTS;
    char infix[MAX_EXPR_SIZE];
    char postfix[MAX_EXPR_SIZE];
    char user_postfix[MAX_EXPR_SIZE];
    int expr_size = 4;  // 초기 식 길이

    printf("inpostfix - by 계산고등학교 20203 김도현 (2024)\n");
    printf("게임 시작!\n\n");

    while (hearts > 0) {
        generate_random_infix(infix, expr_size);
        infix_to_postfix(infix, postfix);

        printf("남은 하트: %d", hearts);
        printf("  점수: %d\n", expr_size - 4);
        printf("중위표기식: %s\n", infix);
        printf("후위표기식으로 변환하세요: ");
        scanf("%s", user_postfix);

        if (strcmp(postfix, user_postfix) == 0) {
            printf("정답입니다!\n\n");
            expr_size++;  // 정답일 때 식 길이 증가
        } else {
            hearts--;
            printf("틀렸습니다.\n");
            printf("정답은: %s\n\n", postfix);
        }

        if (hearts == 0) {
            printf("게임 오버!\n");
            printf("최종 점수: %d\n", expr_size - 4);
        }
    }
}

int main() {
    start_game();
    return 0;
}