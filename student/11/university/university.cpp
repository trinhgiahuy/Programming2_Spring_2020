/* Name: Huy Trinh
* Student number: 290290
* UserID: bdgitr
* E-Mail: giahuy.trinh@tuni.fi
*/
#include "university.hh"

University::University():running_number_(111111)
{
}

University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}

void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}

void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin(); iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}

void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}

void University::add_instance(Params params)
{
    //examine the error cannot find the course
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout<< CANT_FIND << params.at(0)<<std::endl;
        return;
    }

        //examine the error instance exist
    Course* temp_course_iter=courses_.at(params.at(0));
    if(temp_course_iter->has_instance(params.at(1))){
          std::cout<<INSTANCE_EXISTS<<std::endl;
          return ;
    }
    //add new instance
    Instance* n_instance = new Instance(params.at(1),utils::today,temp_course_iter);
    temp_course_iter->new_instance(n_instance);

}

void University::sign_up_on_course(Params params)
{
    //examine the error course code
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout<< CANT_FIND << params.at(0)<<std::endl;
        return;
    }
     Course* temp_course_iter=courses_.at(params.at(0));
     if(!(temp_course_iter->has_instance(params.at(1)))){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
     }
     if(accounts_.find(stoi(params.at(2))) == accounts_.end()){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
     }

     Account* temp_account_iter=accounts_.at(stoi(params.at(2)));

     Instance* iter = temp_course_iter->get_instance(params.at(1));

    if(!(iter->get_date() < utils::today) ){

        iter->add_student_to_instance(temp_account_iter);
        temp_account_iter->add_instance_to_student(temp_course_iter->get_instance(params.at(1)));
        std::cout<<SIGNED_UP<<std::endl;
   }else{
        std::cout<<LATE<<std::endl;
        return ;
   }

}

void University::complete_course(Params params)
{
    //examine the error course code
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout<< CANT_FIND << params.at(0)<<std::endl;
        return;
    }
     Course* temp_course_iter=courses_.at(params.at(0));
     if(!(temp_course_iter->has_instance(params.at(1)))){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
     }
     if(accounts_.find(stoi(params.at(2))) == accounts_.end()){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
     }

     Account* temp_account_iter=accounts_.at(stoi(params.at(2)));

     Instance* iter = temp_course_iter->get_instance(params.at(1));

    if(!(iter->get_date() < utils::today) ){

        iter->add_student_to_instance(temp_account_iter);
        temp_account_iter->add_instance_to_student(temp_course_iter->get_instance(params.at(1)));
        std::cout<<SIGNED_UP<<std::endl;
   }else{
        std::cout<<LATE<<std::endl;
        return ;
   }
    std::cout<<COMPLETED<<std::endl;

        //erase the completed course from current_ vector
        temp_account_iter->erease_instance(temp_course_iter
                                           ->get_instance(params.at(1)));

        //add the completed course to complete_ vector
        temp_account_iter->add_complete(temp_course_iter);

}

void University::print_signups(Params params)
{
    //examine the error cannot find the matching course
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout<<CANT_FIND<<params.at(0)<<std::endl;
        return;
    }

    //print the sign up
    Course* temp_course_iter = courses_.at(params.at(0));
    temp_course_iter->print_signups();

}

void University::print_study_state(Params params)
{
    //examine the error cannot find the matching student account
    if(accounts_.find(stoi(params.at(0)))==accounts_.end()){
        std::cout<<CANT_FIND<<params.at(0)<<std::endl;
        return;
    }

    //print the study state data of account
    Account* temp_account_iter = accounts_.at(stoi(params.at(0)));
    temp_account_iter->print_current();
    print_completed(params);

}

void University::print_completed(Params params)
{
    //examine the error cannot find the matching student account
    if(accounts_.find(stoi(params.at(0)))==accounts_.end()){
        std::cout<<CANT_FIND<<params.at(0)<<std::endl;
        return;
    }

    //print complete course data
    Account* temp_account_iter=accounts_.at(stoi(params.at(0)));
    temp_account_iter->print_complete();
    std::cout<<"Total credits: "<<temp_account_iter->get_complete_credit()<<std::endl;
}

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
