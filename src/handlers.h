#ifndef HANDLERS_H
#define HANDLERS_H

char *handle_root(const char* body);
char *handle_create_user(const char* body);
char *handle_login_user(const char* body);

#endif // !HANDLERS_H
