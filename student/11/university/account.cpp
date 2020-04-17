/* Name: Huy Trinh
* Student number: 290290
* UserID: bdgitr
* E-Mail: giahuy.trinh@tuni.fi
*/
#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::add_instance_to_student(Instance* iter){
    current_.push_back(iter);
}

bool Account::has_instace(std::string name){
    for(auto iterator : current_){
        if(iterator->get_name()==name){
            return true;
        }
      }
   return false;
}

void Account::erease_instance(Instance *instance_iter){
   std::vector<Instance*>::iterator iter = std::find(current_.begin(), current_.end(), instance_iter);
   if ( iter != current_.end() ){
       current_.erase(iter);
   }

}

void Account::add_complete(Course *iter){
    completed_.push_back(iter);
}


void Account::print_current(){
    std::cout<<"Current:"<<std::endl;
    for(auto iter : current_){
        Course* temp_course_instant=iter->get_course_iter();
        //print current course'data in one line
        temp_course_instant->print_info(false);
                std::cout<<" "<<iter->get_name()<<std::endl;
    }
    std::cout << "Completed: " << std::endl;
}
void Account::print_complete(){
    for(auto iter: completed_){
        iter->print_info(true);
    }
}

const int Account::get_account_number()
{
    return account_number_;
}

int Account::get_complete_credit(){
    int total_credit=0;
    for(auto iter: completed_){
        total_credit += iter->get_credits();
    }
    return total_credit;
}



