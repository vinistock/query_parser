/**
 * Query parser
 *
 * Copyright (c) 2020 Vinicius Stock
 * Available under the MIT License
 */

%%{
    machine parser;

    main := ("foo" | "bar");
}%%

%% write data;

int main() {
    %% write init;
    %% write exec;
    return 0;
}
