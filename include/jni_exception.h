#define ERROR_MESSAGE_LENGTH 1024*5    //Error message length
#define JNI_EXCEPTION_CLASS_NAME "org/tutorial/jni/util/exception/JniException" //Java Exception class name
#include <setjmp.h>

jmp_buf jump_buffer;                     //to save the program state

/***********************************************************************************
Assert definition.
When the condition fails, call the function with the file,line,
and the error information.
__FILE__' and '__LINE__' are predefined macros and part of the C/C++ standard. 
During preprocessing, they are replaced respectively by a constant string holding 
the current file name and by a integer representing the current line number.
***********************************************************************************/

#define JNI_ASSERT(_EXPRESSION_ ,_INFO_) \
if (!(_EXPRESSION_)) \
  RestoreProgramState(__FILE__,__LINE__, \
      _INFO_); \

/***********************************************************************************
Restore the program state into the saved state (the program state is saved by setjmp)
***********************************************************************************/
#define RESTORE_SAFE_STATE() \
   longjmp(jump_buffer,1);\

/***********************************************************************************
Save the program state. This saved state can be restored by longjmp
***********************************************************************************/
#define SAVE_PGM_STATE()\
    if (setjmp(jump_buffer)!=0 )\
    {\
      ThrowJNIException();\
      return 0; \
    }\

/***********************************************************************************
Throw a  Java exception.(No saving of program state)
***********************************************************************************/
#define THROW_JAVA_EXCEPTION(_INFO_) \
   ThrowJNIException(__FILE__,__LINE__, \
      _INFO_); \
/******************************************************************************
throws the exception to java
Param       :const char* pzFile,
             int iLine,
             const char* pzMessage
Return      :
******************************************************************************/
void ThrowJNIException(const char* pzFile = 0, int iLine = 0, const char* pzMessage = 0);
/******************************************************************************
Restore the saved state.
Param       :const char* pzFile,
             int iLine,
             const char* pzMessage
Return      :
******************************************************************************/
void RestoreProgramState(const char* pzFile, int iLine,const char* pzMessage);
