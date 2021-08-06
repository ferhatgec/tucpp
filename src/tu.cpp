// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <iostream>
#include <vector>
#include "../libs/curl4cpp/curl4.hpp"

int main(int argc, char** argv) noexcept {
    if(argc < 2) {
        std::cout << "Tuc - TinyUrl CLI\n" <<
            argv[0] << " {link} ...\n";
        return 1;
    }

    std::vector<std::string> args(argv, argv + argc); args.erase(args.begin());

    curl4::CURL4 init = curl4::easy::init();

    for(auto& arg : args) {
        {
            std::string val;

            init.setopt(CURLOPT_URL, "https://tinyurl.com/api-create.php?url=" + arg);
            init.setopt(CURLOPT_WRITEFUNCTION, curl4::easy::writefunc);
            init.setopt(CURLOPT_WRITEDATA, &val);

            CURLcode res = curl4::easy::perform(init);

            std::cout << arg + " -> " + val << '\n';
        }
    }
}