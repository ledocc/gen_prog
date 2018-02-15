#define BOOST_TEST_MODULE gen_prog__algorithm__set_symetric_difference
#include <boost/test/unit_test.hpp>



#include <gen_prog/algorithm/set_symmetric_difference.hpp>



BOOST_AUTO_TEST_CASE(no_difference)
{
  using IntList = std::vector<int>;

  IntList list1 = {0, 1, 2, 3, 4, 5};
  IntList list2 = {0, 1, 2, 3, 4, 5};

  IntList difference1;
  IntList difference2;

  gen_prog::algorithm::set_symmetric_difference(
                                               list1.begin(), list1.end(),
                                               list2.begin(), list2.end(),
                                               std::back_inserter(difference1),
                                               std::back_inserter(difference2) );

  BOOST_TEST( difference1.empty() );
  BOOST_TEST( difference2.empty() );
}

BOOST_AUTO_TEST_CASE(list1_difference)
{
  using IntList = std::vector<int>;

  IntList list1 = {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7};
  IntList list2 = {        0, 1,       4, 5};

  IntList difference1;
  IntList difference2;

  gen_prog::algorithm::set_symmetric_difference(
                                               list1.begin(), list1.end(),
                                               list2.begin(), list2.end(),
                                               std::back_inserter(difference1),
                                               std::back_inserter(difference2) );

  BOOST_TEST( ( difference1 == IntList{ -2, -1, 2, 3, 6, 7 } ) );
  BOOST_TEST( difference2.empty() );
}

BOOST_AUTO_TEST_CASE(list2_difference)
{
  using IntList = std::vector<int>;

  IntList list1 = {        0, 1,       4, 5};
  IntList list2 = {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7};

  IntList difference1;
  IntList difference2;

  gen_prog::algorithm::set_symmetric_difference(
                                               list1.begin(), list1.end(),
                                               list2.begin(), list2.end(),
                                               std::back_inserter(difference1),
                                               std::back_inserter(difference2) );

  BOOST_TEST( difference1.empty() );
  BOOST_TEST( ( difference2 == IntList{ -2, -1, 2, 3, 6, 7 } ) );
}


BOOST_AUTO_TEST_CASE(list1_and_list2_difference)
{
  using IntList = std::vector<int>;

  IntList list1 = {-4, -3,         0, 1,       4, 5,       8, 9 };
  IntList list2 = {        -2, -1, 0, 1, 2, 3, 4, 5, 6, 7       };

  IntList difference1;
  IntList difference2;

  gen_prog::algorithm::set_symmetric_difference(
                                               list1.begin(), list1.end(),
                                               list2.begin(), list2.end(),
                                               std::back_inserter(difference1),
                                               std::back_inserter(difference2) );

  BOOST_TEST( ( difference1 == IntList{ -4, -3, 8, 9 } ) );
  BOOST_TEST( ( difference2 == IntList{ -2, -1, 2, 3, 6, 7 } ) );
}
