//
//  main.c
//  SortingUsingCoreFoundation
//
//  Created by Panayotis Matsinopoulos on 11/7/21.
//

#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include "Customer.h"

const void *CustomerArrayRetainCallback (CFAllocatorRef allocator, const void *value) {
  printf("CustomerArrayRetainCallback ...\n");
  Customer *customer = (Customer *)value;
  CFRetain(customer->firstName);
  CFRetain(customer->lastName);
  return value;
}

void CustomerArrayReleaseCallBack (CFAllocatorRef allocator, const void *value) {
  printf("CustomerArrayReleaseCallBack ...\n");
  Customer *customer = (Customer *)value;
  CFRelease(customer->firstName);
  CFRelease(customer->lastName);
}

CFStringRef CustomerArrayCopyDescriptionCallBack (const void *value) {
  printf("CustomerArrayCopyDescriptionCallBack ...\n");
  
  Customer customer = *((Customer *)value);
  CFStringRef names[2] = {customer.lastName, customer.firstName};
  CFArrayRef fullName = CFArrayCreate(kCFAllocatorDefault, (const void **)names, 2, &kCFTypeArrayCallBacks);
  CFStringRef result = CFStringCreateByCombiningStrings(kCFAllocatorDefault, fullName, CFSTR(" "));
  CFRelease(fullName);
  
  return result;
}

Boolean CustomerArrayEqualCallBack (const void *value1, const void *value2) {
  printf("CustomerArrayEqualCallBack ...\n");
  
  Customer customer1 = *(Customer *)(value1);
  Customer customer2 = *(Customer *)(value2);
  return CustomersAreEqual(&customer1, &customer2) == kCFCompareEqualTo;
}

int main(int argc, const char * argv[]) {
  const int numberOfCustomers = 3;
  
  CFArrayCallBacks customerCallBacks;
  customerCallBacks.version = 0;
  customerCallBacks.retain = CustomerArrayRetainCallback;
  customerCallBacks.release = CustomerArrayReleaseCallBack;
  customerCallBacks.copyDescription = CustomerArrayCopyDescriptionCallBack;
  customerCallBacks.equal = CustomerArrayEqualCallBack;
  
  Customer* customers[numberOfCustomers] = {
    CreateCustomer(CFSTR("Peter"), CFSTR("Pan")),
    CreateCustomer(CFSTR("Mary"), CFSTR("Foo")),
    CreateCustomer(CFSTR("John"), CFSTR("Woo"))
  };
  
  CFArrayRef cfCustomers = CFArrayCreate(kCFAllocatorDefault,
                                         (const void**)customers,
                                         numberOfCustomers,
                                         &customerCallBacks);
  
  //  PrintCustomers(customers, numberOfCustomers);
  
  //  qsort(customers, numberOfCustomers, sizeof(Customer), CustomerComparison);
  
  printf("After sorting:\n");
  
  //  PrintCustomers(customers, numberOfCustomers);
  
  //  for(int i = 0; i < numberOfCustomers; i++) {
  //    DestroyCustomer(&customers[i]);
  //  }
  //
  CFStringRef customersArrayDescription = CFCopyDescription(cfCustomers);
  CFRetain(customersArrayDescription);
  
  printf("Desc: %s\n", CFStringGetCStringPtr(customersArrayDescription, CFStringGetSystemEncoding()));
  
  CFRelease(customersArrayDescription);
  CFRelease(cfCustomers);
  
  printf("Bye!\n");
  
  return 0;
}
