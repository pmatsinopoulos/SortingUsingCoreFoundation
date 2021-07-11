//
//  Customer.c
//  SortingUsingCoreFoundation
//
//  Created by Panayotis Matsinopoulos on 11/7/21.
//

#include <CoreFoundation/CoreFoundation.h>
#include "Customer.h"

CFComparisonResult CustomersAreEqual(Customer *customer1, Customer *customer2) {
  CFComparisonResult comparisonResultFirstName = CFStringCompare(customer1->firstName, customer2->firstName, 0);
  CFComparisonResult comparisonResultLastName = CFStringCompare(customer1->lastName, customer2->lastName, 0);
  if (comparisonResultLastName == kCFCompareEqualTo) {
    return comparisonResultFirstName;
  }
  return comparisonResultLastName;
}

Customer *CreateCustomer(CFStringRef iFirstName, CFStringRef iLastName) {
  size_t bufferSize = sizeof(Customer);
  Customer *customer = malloc(bufferSize);
  
  customer->firstName = CFStringCreateCopy(kCFAllocatorDefault, iFirstName);
  
  customer->lastName = CFStringCreateCopy(kCFAllocatorDefault, iLastName);
  
  return customer;
}
