#define BOOST_TEST_MODULE decomposer_tests
#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/unit_test.hpp>

int main(int argc, char** argv)
{
  return boost::unit_test_framework::unit_test_main(init_unit_test, argc, argv);
}
