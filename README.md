# c++-unit-test Practice 1: Simple Calculator Project Test
directory: Calculator/Calculator 
description: simple calculator source written by c++
There are five functions(add, sub, div, mult, factorial)

### Test Code
directory: [Calculator/UnitTest2](Calculator/UnitTest2)  
function result test description
- "cal.add" test inputs: int+int(positive or negative), float+float(positive or negative)  
- "cal.sub" test inputs: int-int(positive or negative), float-loat(positive or negative)  
- "cal.div" test inputs: int-int(positive or negative), int/0(try-catch), 0/int  
- "cal.mult" test inputs: int+int(positive or negative), float+float(positive or negative)  
- "cal.factorial" test inputs: 3, 1, 0, -1

# c++-unit-test Practice 2: Simple User ManageMetn Project Test
directory: [ManageMentApplication/ManageMentApplication](ManageMentApplication/ManageMentApplication)  
description: simple User ManageMent(register, login, admin, etc) source written by c++

### Test Code
directory: [ManageMentApplication/UnitTest](ManageMentApplication/UnitTest) 
function result test description
- CheckPermission(): check user authority, if user authority is "W", "RW", return true  
- CheckChangedDisk(): check the number of disk additions, if the number < 3, return true
- CheckUser(): verify user, if user information is valid, return true
- CheckCode(): verify admin code, if the input and admin code are the same, return true
- isNotVaild_ID(): check if input value is same as ID of vaild user, if same, return false
- isNotWait_ID(): check if input value is same as ID of wait user, if same, return false
- isVaild_Passwd(): verify a password foramt,   
   if the password contains lowercase uppercase letters or numbers and is longer than 8, return true
- isNotContain_iden(): Check if password contains Social Security Number, if not contained, return true
- isVaild_Identity(): verify a Social Security Number foramt, if the SSN format is "[0 9]{6}-[0 9]{6}", return true

### doxygen result
directory: [ProjectReport/Doxygen_html](ProjectReport/Doxygen_html)   
see [index.html](ProjectReport/Doxygen_html/index.html)  
function result test description

### etc
directory: [ProjectReport](ProjectReport)   
detailed information is in ProjectReport directory
