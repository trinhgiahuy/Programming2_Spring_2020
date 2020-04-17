
/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  ** Program author
  * Name: Huy Trinh
  * Student number: 290290
  * UserID: bdgitr
  * E-Mail: giahuy.trinh@tuni.fi
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief add_instance_to_student
     * @param iter iterator that point to Instance class
     */
    void add_instance_to_student(Instance* iter);

    /**
     * @brief has_instace check to see if the account has register for the instance
     * @param instance name
     * @return true if the account has the instance or false otherwise
     */
    bool has_instace(std::string name);

    /**
     * @brief erease_instance out of the current_ vector
     * @param instance_iter pointer to point to Instance class
     */
    void erease_instance(Instance* instance_iter);

    /**
     * @brief get_complete_credit
     * @return the credit (int)
     */
    int get_complete_credit();

    /**
     * @brief print_current's data
     */
    void print_current();

    /**
     * @brief add_complete pointer to completed course
     * @param iter iterator that point to Course class
     */
    void add_complete(Course* iter);

    /**
     * @brief print_complete's data
     */
    void print_complete();

    const int get_account_number();
private:

    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
};

#endif // ACCOUNT_HH
