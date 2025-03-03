// Uncomment the next line to use precompiled headers
#include "pch.h"
#include <cstddef>
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

TEST_F(CollectionTest, CanAddToEmptyVector)
{
    ASSERT_EQ(collection->size(), 0);
    add_entries(1);
    ASSERT_EQ(collection->size(), 1);
}

TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    EXPECT_EQ(collection->size(), 0);
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);
}

TEST_F(CollectionTest, VectorMaxSizeGreaterThanOrEqualToSize)
{
    // Test if vector has a max size of greater than or equal to 0 
    EXPECT_EQ(collection->size(), 0);
    ASSERT_GE(collection->max_size(), 0);

    // Test if vector has a max size of greater than or equal to 1
    add_entries(1);
    EXPECT_EQ(collection->size(), 1);
    ASSERT_GE(collection->max_size(), 1);

    // Test if vector has a max size of greater than or equal to 5
    add_entries(4);
    EXPECT_EQ(collection->size(), 5);
    ASSERT_GE(collection->max_size(), 5);

    // Test if vector has a max size of greater than or equal to 10
    add_entries(5);
    EXPECT_EQ(collection->size(), 10);
    ASSERT_GE(collection->max_size(), 10);
}

TEST_F(CollectionTest, VectorCapacityGreaterThanOrEqualToSize)
{
    // Test if vector has a capacity of greater than or equal to 0 
    EXPECT_EQ(collection->size(), 0);
    ASSERT_GE(collection->capacity(), 0);

    // Test if vector has a capacity of greater than or equal to 1
    add_entries(1);
    EXPECT_EQ(collection->size(), 1);
    ASSERT_GE(collection->capacity(), 1);

    // Test if vector has a capacity of greater than or equal to 5
    add_entries(4);
    EXPECT_EQ(collection->size(), 5);
    ASSERT_GE(collection->capacity(), 5);

    // Test if vector has a capacity of greater than or equal to 10
    add_entries(5);
    EXPECT_EQ(collection->size(), 10);
    ASSERT_GE(collection->capacity(), 10);
}


TEST_F(CollectionTest, VectorResizingIncreasesCollection)
{
    // Sanity check, collection is fresh with 0 elements
    EXPECT_EQ(collection->size(), 0);
    collection->resize(10); // Resize capacity to 10
    ASSERT_EQ(collection->size(), 10); // Ensure capacity was updated
}

TEST_F(CollectionTest, VectorResizingDecreasesCollection)
{
    // Sanity check, collection is fresh with 0 elements
    EXPECT_EQ(collection->size(), 0);
    collection->resize(10); // Resize capacity to 10
    EXPECT_EQ(collection->size(), 10); // Ensure capacity was updated

    collection->resize(1); // Resize to 1
    ASSERT_EQ(collection->size(), 1); // Make sure capacity decreased to 1
}

TEST_F(CollectionTest, VectorResizingDecreasesCollectionToZero)
{
    // Sanity check, collection is fresh with 0 elements
    EXPECT_EQ(collection->size(), 0);
    collection->resize(10); // Resize capacity to 10
    EXPECT_EQ(collection->size(), 10); // Ensure capacity was updated

    collection->resize(0); // Resize to 0
    ASSERT_EQ(collection->size(), 0); // Make sure capacity decreased to 0
}

TEST_F(CollectionTest, ClearErasesVector)
{
    // Sanity check, collection is fresh with 0 elements
    EXPECT_EQ(collection->size(), 0);

    add_entries(10); // Add 10 random entries

    EXPECT_EQ(collection->size(), 10); // Expect they were added

    collection->clear(); // Clear the collection
    ASSERT_TRUE(collection->empty()); // Make sure collection is emptied by clear()
}

TEST_F(CollectionTest, EraseClearsVector)
{
    // Sanity check, collection is fresh with 0 elements
    EXPECT_EQ(collection->size(), 0);

    add_entries(10); // Add 10 random entries
    
    EXPECT_EQ(collection->size(), 10);
    
    // Erase all values that were just added
    collection->erase(collection->begin(), collection->end());
    ASSERT_EQ(collection->size(), 0); // Collection should be empty.
}

TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    // Sanity check
    EXPECT_EQ(collection->size(), 0);
   
    // Initial capacity is 0
    ASSERT_EQ(collection->capacity(), 0);
    
    // Reserve 10 blocks of memory without actually adding values
    collection->reserve(10);
    
    // Capacity should be 10, size should still be 0
    ASSERT_EQ(collection->capacity(), 10);
    ASSERT_EQ(collection->size(), 0);
    
}

static TEST_F(CollectionTest, VectorThrowsOutOfRangeExceptionWhenIndexedOutOfBounds)
{
    // Sanity check
    EXPECT_EQ(collection->size(), 0);

    EXPECT_THROW(static_cast<void>(collection->at(1)), std::out_of_range);
}


// NOTE: This is a negative test
TEST_F(CollectionTest, VectorKnowsOriginsOfUniverse)
{
    ASSERT_DEATH({
        collection->push_back(47);
        exit(1);
    }, "Collection is not wise.");
}

TEST_F(CollectionTest, VectorShrinksToFit)
{
    // Sanity check
    EXPECT_EQ(collection->size(), 0);
   
    // Initial capacity is 0
    ASSERT_EQ(collection->capacity(), 0);
    
    collection->reserve(100); // malloc 100 * sizeof whatever the vector holds
   
    ASSERT_EQ(collection->capacity(), 100); // Collection's capacity should now be 100

    add_entries(25); // Use up 25 of the 100 available memory blocks

    collection->shrink_to_fit(); // Shrink from 100 to 25

    ASSERT_EQ(collection->capacity(), 25);// capacity should now equal the number of elements in the vector
}


typedef struct {
    char username[10];
    char password[10];
} User;

void set_username(User *user, char *new_username) {
    strcpy(user->username, new_username); // Unsafe!!
}

TEST_F(CollectionTest, UpdateUsernameUnsafe) {
    User user = {
       "username\0",
       "password\0"
    };
    std::cout << "Before updating username:" << std::endl;
    std::cout << "Username is: " << user.username << std::endl;
    std::cout << "Password is: " << user.password << std::endl;
    char new_username[20] = "tombrady1 hacked\0";
    set_username(&user, new_username);
    user.username[9] = '\0';

    std::cout << "Updated username: " << user.username << std::endl;
    std::cout << "Updated password: " << user.password << std::endl;

    // Save new password to database to propagate changes...

    ASSERT_STREQ(user.password, "password");
}

void set_username_safe(User *user, char *new_username) {
    // use strncpy, which only copies the first n bytes of source into dest
    strncpy(user->username, new_username, strlen(user->username));
}

TEST_F(CollectionTest, UpdateUsernameSafe) {
    User user = {
       "username\0",
       "password\0"
    };
    std::cout << "Before updating username:" << std::endl;
    std::cout << "Username is: " << user.username << std::endl;
    std::cout << "Password is: " << user.password << std::endl;
    char new_username[20] = "tombrady1 hacked\0";
    set_username_safe(&user, new_username);
    user.username[9] = '\0';

    std::cout << "Updated username: " << user.username << std::endl;
    std::cout << "Updated password: " << user.password << std::endl;
    ASSERT_STREQ(user.password, "password");
}

typedef struct {
    char description[16];
    void(*fp)();
} Data;

void safe_func() {
    std::cout << "Perimeter secured." << std::endl;
}

void super_dangerous_hacker_func() {
    std::cout << "Participating in highly nefarious activities." << std::endl;
}

void set_description(Data *data, const char *description) {
    // la di da strcpy without validation, nothing to see here
    strcpy(data->description, description);
}

TEST_F(CollectionTest, StrcpyArbitraryCodeExecutionUnsafe) {
    
    Data data = {
        "A description",
        safe_func
    };

    data.fp();
    std::cout << "Data struct addr:           " << &data << std::endl;
    std::cout << "Data description addr:      " << &data.description << std::endl;
    std::cout << "Data function addr:         " << &data.fp << std::endl;
    std::cout << "Data function pointer addr: " << data.fp << std::endl;
    std::cout << "addr of safe_func:          " << &safe_func << std::endl;
    
    void (*exploit)() = super_dangerous_hacker_func;
    char new_desc[48] = "the mitochondria is the powerhouse of the cell";
    memcpy(new_desc + 16,  &exploit, sizeof(&super_dangerous_hacker_func));
    set_description(&data, new_desc);
    std::cout << "After exploit: " << std::endl;
    data.fp();
    std::cout << "Data description:       " << data.description << std::endl;
    std::cout << "Data function ptr addr: " << data.fp << std::endl;
    std::cout << "addr of hacker func:    " << &super_dangerous_hacker_func << std::endl;
    
    ASSERT_EQ((void*)data.fp, (void*)safe_func);
}

void set_description_safe(Data* data, const char* new_description) {
    strncpy(data->description, new_description, sizeof(data->description));
}

TEST_F(CollectionTest, StrcpyArbitraryCodeExecutionSafe) {
    Data data = {
        "A description",
        safe_func
    };

    data.fp();
    std::cout << "Data struct addr:           " << &data << std::endl;
    std::cout << "Data description addr:      " << &data.description << std::endl;
    std::cout << "Data function addr:         " << &data.fp << std::endl;
    std::cout << "Data function pointer addr: " << data.fp << std::endl;
    std::cout << "addr of safe_func:          " << &safe_func << std::endl;
    
    void (*exploit)() = super_dangerous_hacker_func;
    char new_desc[48] = "the mitochondria is the powerhouse of the cell";
    memcpy(new_desc + 16,  &exploit, sizeof(&super_dangerous_hacker_func));
    set_description_safe(&data, new_desc);
    std::cout << "After exploit: " << std::endl;
    data.fp();
    std::cout << "Data description:       " << data.description << std::endl;
    std::cout << "Data function ptr addr: " << data.fp << std::endl;
    std::cout << "addr of hacker func:    " << &super_dangerous_hacker_func << std::endl;
    
    ASSERT_EQ((void*)data.fp, (void*)safe_func);
}
