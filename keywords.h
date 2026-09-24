#ifndef KEYWORDS_H
#define KEYWORDS_H

struct flagables keyphrases[] = {
    // Critical execution & reverse shells (Weight: 20-30)
    {"| bash",                     20},
    {"| sh",                       20},
    {"| zsh",                      20},
    {"rm -rf /",                   30},
    {"rm -rf ~",                   25},
    {"rm -rf $HOME",               25},
    {"rm -rf \"$HOME\"",           25},
    {"/etc/sudoers",               25},
    {"/etc/shadow",                25},
    {"/etc/ld.so.preload",         25},
    {"LD_PRELOAD",                 20},
    {"chmod +x /",                 20},
    {"chmod+x /",                  20},
    {"chmod 777 /",                20},
    {"nc -e",                      20},
    {"ncat -e",                    20},

    // Suspicious exfiltration endpoints (Weight: 15)
    {"discord.com/api/webhooks",   15},
    {"api.telegram.org",           15},

    // Remote code fetching & execution outside standard sources (Weight: 8-10)
    {"raw.githubusercontent.com",  8},
    {"pastebin.com",               10},

    // Execution / Dynamic interpretation (Weight: 7-8)
    {"eval ",                      8},
    {"python -c",                  7},
    {"python3 -c",                 7},
    {"perl -e",                    7},
    {"ruby -e",                    7},

    // Obfuscation and decoding (Weight: 8)
    {"base64 -d",                  8},
    {"base64 --decode",            8},
    {"openssl enc",                8},
    {"xxd -r",                     8},

    // Checksum tampering (empty sums) (Weight: 8)
    {"md5sums=('')",               8},
    {"sha256sums=('')",            8},
    {"b2sums=('')",                8},

    // Pirated / sketchy indicators (Weight: 4-5)
    {"-patched",                   3},
    {"-cracked",                   5},
    {"-unlock",                    5},
};

int num_keywords = sizeof(keyphrases) / sizeof(keyphrases[0]);

#endif

