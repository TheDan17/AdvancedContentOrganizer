//#include "resulthandler.h"

/*
// common Result
template <typename ResultT, typename ErrorT>
Result<ResultT, ErrorT>::Result(ErrorT error){
    this->err = error;
    this->is_not_err = false;
}

template <typename ResultT, typename ErrorT>
ErrorT Result<ResultT, ErrorT>::error(){
    if (this->is_not_err)
        throw std::logic_error(ErrorStrings::undefined_result_error);
    else
        return this->err;
}

template <typename ResultT, typename ErrorT>
bool Result<ResultT, ErrorT>::is_ok(){
    return this->is_not_err;
}


// value Result
template <typename ResultT, typename ErrorT>
Result<ResultT, ErrorT>::Result(ResultT value){
    this->val = value;
    this->is_not_err = true;
}

template <typename ResultT, typename ErrorT>
ResultT Result<ResultT, ErrorT>::value(){
    if (this->is_not_err)
        return this->val;
    else
        throw std::logic_error(ErrorStrings::undefined_result_value);
}


// pointer Result
template <typename ResultT, typename ErrorT>
Result<ResultT*, ErrorT>::Result(ResultT* value){
    this->val = value;
    this->is_not_err = true;
}

template <typename ResultT, typename ErrorT>
ResultT* Result<ResultT*, ErrorT>::value(){
    return this->val;
}


// functions Result

template <typename ErrorT>
Result<void, ErrorT> error(std::string err_msg){
    return Result<void, ErrorT>(ErrorT(err_msg));
}

template <typename ResultT>
Result<ResultT> value(ResultT value){
    return Result<ResultT>(value);
}

*/











/*
template <typename ErrorType>
bool ResultBase<ErrorType>::is_success(){
    if(this->error.has_value())
        return false;
    else
        return true;
}

template <typename ErrorType>
ErrorType ResultBase<ErrorType>::get_error() {
    if(!this->is_success())
        return this->error;
    else
        throw std::runtime_error(ErrorStrings::undefined_result_error);
}


template <typename ResultType, typename ErrorType>
ResultVal<ResultType, ErrorType>::ResultVal(ResultType value) {
    this->value = value;
}

template <typename ResultType, typename ErrorType>
ResultVal<ResultType, ErrorType>::ResultVal(ErrorType error) {
    this->error = error;
}

template <typename ResultType, typename ErrorType>
ResultType ResultVal<ResultType, ErrorType>::get_value() {
    if (this->is_success())
        return this->value;
    else
        throw std::runtime_error(ErrorStrings::undefined_result_value);
}


template <typename ResultType, typename ErrorType>
ResultPtr<ResultType, ErrorType>::ResultPtr(ResultType* value) {
    this->value = value;
}

template <typename ResultType, typename ErrorType>
ResultPtr<ResultType, ErrorType>::ResultPtr(ErrorType error) {
    this->error = error;
}

template <typename ResultType, typename ErrorType>
ResultType* ResultPtr<ResultType, ErrorType>::get_value() {
    if (this->is_success())
        return this->value;
    else
        throw std::runtime_error(ErrorStrings::undefined_result_value);
}
*/
