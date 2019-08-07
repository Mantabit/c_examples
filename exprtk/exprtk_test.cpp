#include <iostream>
#include <exprtk.hpp>

template <typename T>
void test_function(T start,T end,int intervals)
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef exprtk::expression<T>     expression_t;
   typedef exprtk::parser<T>             parser_t;

   std::string expression_string = "switch{ \
           case x<2.5: 	round(0.5+0.5sin(2*pi*x));\
           case x<5: 	2;\
           default: 	5;\
   }";

   T x;

   symbol_table_t symbol_table;
   symbol_table.add_variable("x",x);
   symbol_table.add_constants();

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   parser_t parser;
   parser.compile(expression_string,expression);

   for (x = T(start); x <= T(end); x += (T(end)-T(start))/intervals)
   {
      T y = expression.value();
      printf("%19.15f\t%19.15f\n",x,y);
   }
}

int main(int argc,char** argv){
    test_function<double>(0,5,100);
    return 0;
}
