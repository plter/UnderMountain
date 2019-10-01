//
// Created by plter on 2019/10/1.
//

#ifndef UNDERMOUNTAIN_FORMDATAVALUEITEM_H
#define UNDERMOUNTAIN_FORMDATAVALUEITEM_H

#include <string>

namespace um {
    class FormDataValueItem {
    public:

        FormDataValueItem(std::string name, std::string body, std::string filename = "");

        [[nodiscard]] const std::string &getName() const;


        [[nodiscard]] const std::string &getFilename() const;


        [[nodiscard]] const std::string &getBody() const;


    private:
        std::string _name;
        std::string _filename;
        std::string _body;
    };
}


#endif //UNDERMOUNTAIN_FORMDATAVALUEITEM_H
