/* Name: Huy Trinh
* Student number: 290290
* UserID: bdgitr
* E-Mail: giahuy.trinh@tuni.fi
*/
#include "instance.hh"
#include "course.hh"

Instance::Instance(std::string name,Date date, Course*iter):instance_name(name),instance_date(date),course_iter(iter){
}


bool Instance::is_named(const std::string &name)
{
    if(instance_name == name){
        return true;
    }
    return false;
}

const std::string Instance::get_name()
{
    return instance_name;
}

Date Instance::get_date()
{
    return instance_date;
}

bool Instance::check_account(const int account_num)
{
    for(auto iter : students_vct){
        if(iter->get_account_number()==account_num){
            return true;
        }
    }
    return false;
}

void Instance::add_student_to_instance(Account* iter)
{
    students_vct.push_back(iter);
}

void Instance::print()
{
    std::cout<<instance_name<<std::endl;
    std::cout<<INDENT<<"Starting date: ";
               instance_date.print();
    std::cout<<std::endl;
    std::cout<<INDENT<<"Amount of students: "<<students_vct.size()<<std::endl;
}

void Instance::print_students()
{
    for(auto iter : students_vct){
        std::cout << INDENT;
        iter->print();
    }
}

Course* Instance::get_course_iter(){
    return course_iter;
}


