#include <string>
#include <cmath>
using namespace std;
#include "val.h"

Value Value::operator+(const Value& op) const {

    if (IsInt() && op.IsInt()) {
        return Value(GetInt() + op.GetInt());
    }
    else if (IsReal() && op.IsReal()) {
        return Value(GetReal() + op.GetReal());
    }
    else if (IsInt() && op.IsReal()) {
        return Value(GetInt() + op.GetReal());
    }
    else if (IsReal() && op.IsInt()) {
        return Value(GetReal() + op.GetInt());
    }
    else if (IsString() && op.IsString()) {
        try {
            double val1 = stod(GetString());
            double val2 = stod(op.GetString());
            return Value(val1 + val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsReal()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 + op.GetReal());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsReal() && op.IsString()) {
        try {
            double val2 = stod(op.GetString());
            return Value(GetReal() + val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsInt()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 + op.GetInt());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }

    return Value();
}

Value Value::operator-(const Value& op) const {
    if (IsInt() && op.IsInt()) {
        return Value(GetInt() - op.GetInt());
    }
    else if (IsReal() && op.IsReal()) {
        return Value(GetReal() - op.GetReal());
    }
    else if (IsInt() && op.IsReal()) {
        return Value(GetInt() - op.GetReal());
    }
    else if (IsReal() && op.IsInt()) {
        return Value(GetReal() - op.GetInt());
    }
    else if (IsString() && op.IsString()) {
        try {
            double val1 = stod(GetString());
            double val2 = stod(op.GetString());
            return Value(val1 - val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsReal()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 - op.GetReal());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsReal() && op.IsString()) {
        try {
            double val2 = stod(op.GetString());
            return Value(GetReal() - val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsInt()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 - op.GetInt());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }

    return Value();
}


Value Value::operator*(const Value& op) const {
    if (IsInt() && op.IsInt()) {
        return Value(GetInt() * op.GetInt());
    }
    else if (IsReal() && op.IsReal()) {
        return Value(GetReal() * op.GetReal());
    }
    else if (IsInt() && op.IsReal()) {
        return Value(GetInt() * op.GetReal());
    }
    else if (IsReal() && op.IsInt()) {
        return Value(GetReal() * op.GetInt());
    }
    else if (IsString() && op.IsString()) {
        try {
            double val1 = stod(GetString());
            double val2 = stod(op.GetString());
            return Value(val1 * val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsReal()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 * op.GetReal());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsReal() && op.IsString()) {
        try {
            double val2 = stod(op.GetString());
            return Value(GetReal() * val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsInt()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 * op.GetInt());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsInt() && op.IsString()) {
        try {
            double val1 = stod(op.GetString());
            return Value(GetInt() * val1);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }

    return Value();
}

Value Value::operator/(const Value& op) const {
    if (IsErr() || op.IsErr()) {
        return Value();
    }

    if (IsInt() && op.IsInt()) {
        if (op.GetInt() == 0) {
           cout << "div by zero" << endl;
           return Value();
        }
        return Value(GetInt() / op.GetInt());
    }
    else if (IsReal() && op.IsReal()) {
        if (op.GetReal() == 0.0) {
            cout << "div by zero" << endl;
            return Value();
        }
        return Value(GetReal() / op.GetReal());
    }
    else if (IsInt() && op.IsReal()) {
        if (op.GetReal() == 0.0) {
            cout << "div by zero" << endl;
            return Value();
        }
        return Value(GetInt() / op.GetReal());
    }
    else if (IsReal() && op.IsInt()) {
        if (op.GetInt() == 0.0) {
            cout << "div by zero" << endl;
            return Value();
        }
        return Value(GetReal() / op.GetInt());
    }
    else if (IsString() && op.IsString()) {
        try {
            double val1 = stod(GetString());
            double val2 = stod(op.GetString());
            if (val2 == 0.0) {
                cout << "div by zero" << endl;
                return Value();
            }
            return Value(val1 / val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsReal()) {
        try {
            double val1 = stod(GetString());
            if (op.GetReal() == 0.0) {
                cout << "div by zero" << endl;
                return Value();
            }
            return Value(val1 / op.GetReal());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsReal() && op.IsString()) {
        try {
            double val2 = stod(op.GetString());
            if (val2 == 0.0) {
                cout << "div by zero" << endl;
                return Value();
            }
            return Value(GetReal() / val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsInt()) {
        try {
            double val1 = stod(GetString());
            if (op.GetInt() == 0) {
                cout << "div by zero" << endl;
                return Value();
            }
            return Value(val1 / op.GetInt());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }


    return Value();
}


Value Value::operator==(const Value& op) const {
    if (IsInt() && op.IsInt()) {
        return Value(GetInt() == op.GetInt());
    }
    else if (IsReal() && op.IsReal()) {
        return Value(GetReal() == op.GetReal());
    }
    else if (IsInt() && op.IsReal()) {
        return Value(GetInt() == op.GetReal());
    }
    else if (IsReal() && op.IsInt()) {
        return Value(GetReal() == op.GetInt());
    }
    else if (IsString() && op.IsString()) {
        try {
            double val1 = stod(GetString());
            double val2 = stod(op.GetString());
            return Value(val1 == val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsReal()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 == op.GetReal());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsReal() && op.IsString()) {
        try {
            double val2 = stod(op.GetString());
            return Value(GetReal() == val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsInt()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 == op.GetInt());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }

    return Value();
}


Value Value::operator>(const Value& op) const {
    if (IsInt() && op.IsInt()) {
        return Value(GetInt() > op.GetInt());
    }
    else if (IsReal() && op.IsReal()) {
        return Value(GetReal() > op.GetReal());
    }
    else if (IsInt() && op.IsReal()) {
        return Value(GetInt() > op.GetReal());
    }
    else if (IsReal() && op.IsInt()) {
        return Value(GetReal() > op.GetInt());
    }
    else if (IsString() && op.IsString()) {
        try {
            double val1 = stod(GetString());
            double val2 = stod(op.GetString());
            return Value(val1 > val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsReal()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 > op.GetReal());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsReal() && op.IsString()) {
        try {
            double val2 = stod(op.GetString());
            return Value(GetReal() > val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsInt()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 > op.GetInt());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }

    return Value();
}


Value Value::operator<(const Value& op) const {
    if (IsInt() && op.IsInt()) {
        return Value(GetInt() < op.GetInt());
    }
    else if (IsReal() && op.IsReal()) {
        return Value(GetReal() < op.GetReal());
    }
    else if (IsInt() && op.IsReal()) {
        return Value(GetInt() < op.GetReal());
    }
    else if (IsReal() && op.IsInt()) {
        return Value(GetReal() < op.GetInt());
    }
    else if (IsString() && op.IsString()) {
        try {
            double val1 = stod(GetString());
            double val2 = stod(op.GetString());
            return Value(val1 < val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsReal()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 < op.GetReal());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsReal() && op.IsString()) {
        try {
            double val2 = stod(op.GetString());
            return Value(GetReal() < val2);
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if (IsString() && op.IsInt()) {
        try {
            double val1 = stod(GetString());
            return Value(val1 < op.GetInt());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }

    return Value();
}


Value Value::operator^(const Value& op) const {
    if (IsErr() || op.IsErr()) {
        return Value();
    }

    if (IsInt() && op.IsInt()) {
        int result = 1;
        int base = GetInt();
        int exponent = op.GetInt();

        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result *= base;
            }
            base *= base;
            exponent /= 2;
        }

        return Value(result);
    }
    else if (IsReal() && op.IsReal()) {
        return Value(pow(GetReal(), op.GetReal()));
    }
    else if (IsInt() && op.IsReal()) {
        return Value(pow(GetInt(), op.GetReal()));
    }
    else if (IsReal() && op.IsInt()) {
        return Value(pow(GetReal(), op.GetInt()));
    }
    else {
        return Value();
    }
}

Value Value::Catenate(const Value& oper) const {
    if (IsErr() || oper.IsErr()) { 
        return Value(); 
    }

    std::stringstream ss;
    if (IsString()) {
        ss << GetString();
    }
    else if (IsInt()) {
        ss << GetInt();
    }
    else if (IsReal()) {
        ss << GetReal();
    }

    if (oper.IsString()) {
        ss << oper.GetString();
    }
    else if (oper.IsInt()) {
        ss << oper.GetInt();
    }
    else if (oper.IsReal()) {
        ss << oper.GetReal();
    }

    return Value(ss.str());
}


Value Value::Repeat(const Value& op) const {
    double oper;
    if (IsString() && op.IsString()) {
        try {
            oper = stod(op.GetString());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        int times = oper;
        string str = GetString(), newstr = "";
        for (int i = 1; i <= times; i++) {
            newstr += str;
        }
        return Value(newstr);
    }
    else if (IsReal() && op.IsString()) {
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str(), newstr = "";
        try {
            oper = stod(op.GetString());
        }
        catch (invalid_argument& arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        int times = oper;
        for (int i = 1; i <= times; i++) {
            newstr += stroper1;
        }
        return Value(newstr);
    }
    else if (IsReal() && op.IsReal()) {
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str(), newstr = "";
        oper = op.GetReal();
        int times = oper;

        for (int i = 1; i <= times; i++) {
            newstr += stroper1;
        }
        return Value(newstr);
    }
    else if (IsString() && op.IsReal()) {
        oper = op.GetReal();
        int times = oper;
        string str = GetString(), newstr = "";
        for (int i = 1; i <= times; i++) {
            newstr += str;
        }
        return Value(newstr);
    }
    else {
        return Value();
    }
}

Value Value::SEqual(const Value& oper) const {
    if (IsErr() || oper.IsErr()) {
        return Value();
    }
    string string1;
    string string2;
    stringstream ss;

    if (IsString()) {
        string1 = GetString();
    }
    else if (IsInt()) {
        ss << GetInt();
        string1 = ss.str();
        ss.str("");
    }
    else if (IsReal()) {
        ss << GetReal();
        string1 = ss.str();
        ss.str("");
    }

    if (oper.IsString()) {
        string2 = oper.GetString();
    }
    else if (oper.IsInt()) {
        ss << oper.GetInt();
        string2 = ss.str();
        ss.str("");
    }
    else if (oper.IsReal()) {
        ss << oper.GetReal();
        string2 = ss.str();
        ss.str("");
    }

    return Value(string1 == string2);
}

Value Value::SGthan(const Value& oper) const {
    if (IsErr() || oper.IsErr()) {
        return Value();
    }

    string string1;
    string string2;
    stringstream ss;

    if (IsString()) {
        string1 = GetString();
    }
    else if (IsInt()) {
        ss << GetInt();
        string1 = ss.str();
        ss.str("");
    }
    else if (IsReal()) {
        ss << GetReal();
        string1 = ss.str();
        ss.str("");
    }

    if (oper.IsString()) {
        string2 = oper.GetString();
    }
    else if (oper.IsInt()) {
        ss << oper.GetInt();
        string2 = ss.str();
        ss.str("");
    }
    else if (oper.IsReal()) {
        ss << oper.GetReal();
        string2 = ss.str();
        ss.str("");
    }

    return Value(string1 > string2);
}

Value Value::SLthan(const Value& oper) const {
    if (IsErr() || oper.IsErr()) {
        return Value();
    }

    string string1;
    string string2;
    stringstream ss;

    if (IsString()) {
        string1 = GetString();
    }
    else if (IsInt()) {
        ss << GetInt();
        string1 = ss.str();
        ss.str("");
    }
    else if (IsReal()) {
        ss << GetReal();
        string1 = ss.str();
        ss.str("");
    }

    if (oper.IsString()) {
        string2 = oper.GetString();
    }
    else if (oper.IsInt()) {
        ss << oper.GetInt();
        string2 = ss.str();
        ss.str("");
    }
    else if (oper.IsReal()) {
        ss << oper.GetReal();
        string2 = ss.str();
        ss.str("");
    }

    return Value(string1 < string2);
}