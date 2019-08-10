ssize_t readline(int fd, void *vbuf, size_t n) {
    ssize_t num_read;
    ssize_t tot_read;
    char *buf;
    char ch;

    if(n <= 0 || vbuf == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = (char *)vbuf;                 /* No pointer arithmetic on "void *" */
    tot_read = 0;
    for(;;) {
        num_read = read(fd, &ch, 1);    /* Read a single character from fd   */
        if(num_read == -1) {
            if(errno == EINTR)          /* Interrupted -> restart read()     */
                continue;
            else
                return -1;              /* Some other error                  */
        } else if(num_read == 0) {      /* EOF                               */
            if(tot_read == 0)
                return 0;               /* Some bytes read; add '\0'         */
            else
                break;
        } else {                        /* 'num_read' must be 1              */
            if(tot_read < n - 1) {      /* Discard > (n - 1) bytes          */
                tot_read++;
                *buf++ = ch;
            }

            if(ch == '\n')
                break;
        }

        *buf = '\0';
        return tot_read;
    }
}
