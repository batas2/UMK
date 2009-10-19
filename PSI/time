    time_t     now;
    struct tm  *ts;
    char       buf[80];
 
    /* Get the current time */
    now = time(NULL);
 
    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);
    printf("%s\n", buf);