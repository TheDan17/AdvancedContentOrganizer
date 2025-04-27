#ifndef RESULTHANDLER_H
#define RESULTHANDLER_H

#include <optional>
#include <stdexcept>
#include <variant>

#include "strdict.h"

template <typename ResultT = std::monostate, typename ErrorT = std::runtime_error>
class Result {
protected:
    std::optional<ResultT> val;
    std::optional<ErrorT> err;
    bool is_not_err;

    Result(){
        this->val = std::nullopt;
        this->is_not_err = true;
    }
public:
    Result(ResultT value){
        this->val = value;
        this->is_not_err = true;
    }
    Result(ErrorT error){
        this->err = error;
        this->is_not_err = false;
    }

    ResultT value(){
        if (this->is_not_err)
            return this->val.value();
        else
            throw std::logic_error(str::Error::ResultNotValue);
    }
    ErrorT error(){
        if (this->is_not_err)
            throw std::logic_error(str::Error::ResultNotError);
        else
            return this->err.value();
    }
    bool is_ok(){
        return this->is_not_err;
    }

    explicit operator bool(){
        return this->is_ok();
    }
};

template <typename ResultT, typename ErrorT>
class Result<ResultT*, ErrorT> : public Result<ResultT, ErrorT> {
private:
    ResultT* val = nullptr;
public:
    Result(ResultT* value) : Result<ResultT, ErrorT>(){
        this->val = value;
        this->is_not_err = true;
    }
    Result(ErrorT error) : Result<ResultT, ErrorT>(error){}
    ResultT* value(){
        return this->val;
    }
};


template <typename ErrorT = std::runtime_error>
Result<std::monostate, ErrorT> error(std::string err_msg){
    return Result<std::monostate, ErrorT>(ErrorT(err_msg));
}

template <typename ResultT = std::monostate>
Result<ResultT> value(ResultT value = std::monostate()){
    return Result<ResultT>(value);
}
template <typename ResultT = void>
Result<ResultT*> value(ResultT* value){
    return Result<ResultT*>(value);
}

#endif // RESULTHANDLER_H
