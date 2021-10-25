extern bool EM_anyError;

void EM_newline(void);

extern int EM_tokPos;

void EM_error(int, string,...);
void EM_start(string filename);