#pragma once /* ERR.H */
#define exit_on_err(msg) perror(msg);exit(1)