#ifndef BACKLOG_ITMO_CPP_LN_DANDOBRI_MAIN_EXCEPTIONSLN_H
#define BACKLOG_ITMO_CPP_LN_DANDOBRI_MAIN_EXCEPTIONSLN_H
#include <string>
class Exceptions
{
  public:
    std::string error_msg;
    int error_code;
    Exceptions(int error_code, const std::string& error_msg)
    {
      this->error_code = error_code;
      this->error_msg = error_msg;
    }
};
#endif
