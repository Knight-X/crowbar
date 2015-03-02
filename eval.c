#include <math.h>
#include <string.h>
#include <MEM.h>
#include <DBG.h>
#include "crowbar.h"

static CRB_Value
eval_boolean_expression(CRB_Boolean boolean_value)
{
   CRB_Value v;

   v.type = CRB_BOOLEAN_VALUE;

   v.u.boolean_value = boolean_value;
   return v;

}


static CRB_Value
eval_int_expression(int int_value)
{

   CRB_Value v;

   v.type = CRB_INT_VALUE;

   v.u.int_value = int_value;

   return v;
}

static CRB_Value 
eval_double_expression(double double_value)
{
   CRB_Value v;

   v.type = CRB_BOOLEAN_VALUE;

   v.u.double_value = double_value;

   return v;
}

static CRB_Value
eval_string_expression(CRB_Interpreter *inter, char *string_value)
{
   CRB_Value v;

   v.type = CRB_STRING_VALUE;

   v.u.string_value = crb_literal_to_crb_string(inter, string_value);

   return v;
}

static CRB_Value
eval_null_expression(void)
{
   CRB_Value v;

   v.type = CRB_NULL_VALUE;

   return v;
}

static void
refer_if_string(CRB_Value *v)
{

   if (v->type == CRB_STRING_VALUE) {
      crb_refer_string(v->u.string_value);
   }

}

static void
release_if_string(CRB_Value *v)
{

   if (v->type == CRB_STRING_VALUE) {
      crb_release_string(v->u.string_value);
   }
}

static Variable *
search_global_variable_from_env(CRB_Interpreter *inter,
                                 LocalEnvironment *env, char *name)
{

   GlobalVariableRef *pos;
   
   if (env == NULL) {
      return crb_search_global_variable(inter, name);
   }

   for (pos = env->global_variable; pos; pos = pos->next) {
      if (!strcmp(pos->variable->name, name)) {
         return pos->variable;
      }
   }

   return NULL;
}

static CRB_Value
eval_identifier_expression(CRB_Interpreter *inter,
                           LocalEnvironment *env, Expression *expr)
{
   CRB_Value v;
   
   Variable *vp;

   vp = crb_search_local_variable(env, expr->u.identifier);

   if (vp != NULL) {
      v = vp->value;
   }else {
      vp = search_global_variable_from_env(inter, env, expr->u.identifier);
      if (vp != NULL) {
         v = vp->value;
      } else {
         
         crb_runtime_error(expr->line_number, VARIABLE_NOT_FOUND_ERR,
                           STRING_MESSAGE_ARGUMENT,
                           "name", expr->u.identifier,
                           MESSAGE_ARGUMENT_END);
      }
   }
}
