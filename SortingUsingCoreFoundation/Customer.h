//
//  Customer.h
//  SortingUsingCoreFoundation
//
//  Created by Panayotis Matsinopoulos on 11/7/21.
//

#ifndef Customer_h
#define Customer_h

#include <CoreFoundation/CoreFoundation.h>

typedef struct {
  CFStringRef firstName;
  CFStringRef lastName;
} Customer;

CFComparisonResult CustomersAreEqual(Customer *customer1, Customer *customer2);
Customer *CreateCustomer(CFStringRef iFirstName, CFStringRef iLastName);

#endif /* Customer_h */
