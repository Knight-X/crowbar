#include "MEM.h"
#include "DBG.h"
#define GLOBAL_VARIABLE_DEFINE
#include "crowbar.h"

static void
add_native_functions(CRB_Interpreter *inter)
{
   CRB_add_native_function(inter, "print", crb_nv_print_proc);
   CRB_add_native_function(inter, "fopen", crb_nv_fopen_proc);
   CRB_add_native_function(inter, "fclose", crb_nv_fclose_proc);
   CRB_add_native_function(inter, "fgets", crb_nv_fgets_proc);
   CRB_add_native_function(inter, "fputs", crb_nv_fputs_proc);
}


CRB_Interpreter *
CRB_create_interpreter(void)
{
   MEM_Storage storage;
   CRB_Interpreter *interpreter;

   storage = MEM_open_storage(0);

   interpreter = MEM_storage_malloc(storage,
                                    sizeof(struct CRB_Interpreter_tag));

   interpreter->interpreter_storage = storage;
   interpreter->execute_storage = NULL;
   interpreter->variable = NULL;
   interpreter->function_list = NULL;
   interpreter->statement_list = NULL;
   interpreter->current_line_number = 1;

   crb_set_current_interpreter(interpreter);
   add_native_functions(interpreter);

   return interpreter;
}
