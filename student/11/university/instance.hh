/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 * Name: Huy Trinh
 * Student number: 290290
 * UserID: bdgitr
 * E-Mail: giahuy.trinh@tuni.fi

 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    /**
     * @brief Instance constructor
     * @param name of instance
     * @param date that instance added
     * @param iter pointer to course instance belonging to
     */
    Instance(std::string name,Date date, Course*iter);

    /**
     * @brief is_named
     * @param name of instance
     * @return true if there is instance in course or false otherwise
     */
    bool is_named(const std::string& name);

    /**
     * @brief print instance's starting date and amount of student of that instance
     */

    void print();

    /**
     * @brief print_students's information of that instance
     */
    void print_students();

    /**
     * @brief add_student_to_instance vector which contain pointer to class Account
     * @param iter pointer that point to Account
     */
    void add_student_to_instance(Account* iter);

    /**
     * @brief get_course_iter
     * @return the pointer that point to class Course
     */
    Course* get_course_iter();

    /**
     * @brief get_name
     * @return a name of the instance
     */
    const std::string get_name();

    /**
     * @brief get_date
     * @return the date of the instance
     */
    Date get_date();

    bool check_account(Account *signup);

private:
    /**
     * students_vct that contains the pointer that point to
     * student that has registed for the instance
     */
    std::vector<Account*>students_vct;

    const std::string instance_name;

    Date instance_date ;

    Course* course_iter;

};

#endif // INSTANCE_HH
