#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <calc.h>

#define Assert(e) ((e) ? (void)0 : fprintf(stderr, ">> Assertion Failure:("#e") - \""__FILE__":%d\"\n", __LINE__))
#define Assertr(e) if(e) (void)0; else return (1 | fprintf(stderr, ">> Assertion Failure:("#e") - \""__FILE__":%d\"\n", __LINE__));

int main(int argc, char *argv[])
{
    Assertr(calcEvaluate);
    Assert(0.0 == calcEvaluate(""));
    Assert(isnan(calcEvaluate("0.,")));
    Assert(0.0 == calcEvaluate("0.0"));
    Assert(-0.0 == calcEvaluate("-0.0"));
    Assert(-0.0 == calcEvaluate("-0"));
    Assert(1.0 == calcEvaluate("1"));
    Assert(3.141592653 == calcEvaluate("3.141592653"));
    Assert(-4.0 == calcEvaluate("-4"));
    Assert(((double)-1) == calcEvaluate("-1"));
    Assert(((double)-1.5) == calcEvaluate("-1.5"));
    Assert(((double)5) == calcEvaluate("5"));
    Assert(((double)+5.532) == calcEvaluate("+5.532"));
    Assert(((double)-5.5+2) == calcEvaluate("-5.5+2"));
    Assert(((double)5*(5+5)/2) == calcEvaluate("5*(5+5)/2"));
    Assert(((double)5*(5+5)/2) == calcEvaluate(" 5 * ( 5 +5) / 2 "));
    Assert(isnan(calcEvaluate("5 5")));
    Assert(isnan(calcEvaluate(" 5 5")));
    Assert(isnan(calcEvaluate(" 5 5 ")));
    Assert(isnan(calcEvaluate(" 4+45 5 ")));
    return 0;
}