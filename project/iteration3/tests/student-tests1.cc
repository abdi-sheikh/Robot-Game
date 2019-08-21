/* STUDENTS: Write your own unit tests in this file.  Or, better yet,
   rename this file to something more meaningful and/or add additional
   files of tests to this directory to test your project code in
   whatever ways you see fit!
 */

// The Google Test framework
#include <gtest/gtest.h>
// Includes for project code in the ../src directory

#include "../src/sensor_distress.h"
#include "../src/sensor_entity.h"
#include "../src/sensor_proximity.h"

#ifdef STUDENT_TEST

TEST(StudentTest, DistressActivate) {
  csci3081::SensorDistress st;


  EXPECT_EQ(st.distressed(), 0);

  st.distressed(1);
  EXPECT_EQ(st.distressed(), 1);
}

TEST(StudentTest, DistressReset) {
  csci3081::SensorDistress st;
  st.distressed(1);
  EXPECT_EQ(st.distressed(), 1);

  st.Reset();
  EXPECT_EQ(st.distressed(), 0);
}



TEST(StudentTest, ProximityActivate) {
  csci3081::SensorProximity st;

  EXPECT_EQ(st.activatedProx(), 0);

  st.activatedProx(1);
  EXPECT_EQ(st.activatedProx(), 1);
}

TEST(StudentTest, ProximityReset) {
  csci3081::SensorProximity st;

  st.activatedProx(1);
  EXPECT_EQ(st.activatedProx(), 1);

  st.Reset();
  EXPECT_EQ(st.activatedProx(), 0);
}

TEST(StudentTest, ProximityRange) {
  csci3081::SensorProximity st;

  st.range(5);
  EXPECT_EQ(st.range(),5);
}

TEST(StudentTest, ProximityFieldofView) {
  csci3081::SensorProximity st;

  st.fieldofView(12 * M_PI);
  EXPECT_EQ(st.fieldofView(),5);
}


TEST(StudentTest, EntityActivate) {
  csci3081::SensorEntity st;



  EXPECT_EQ(st.distressed(), 0);

  st.distressed(1);
  EXPECT_EQ(st.distressed(), 1);
}

TEST(StudentTest, EntityReset) {
  csci3081::SensorEntity st;

  st.distressed(1);
  EXPECT_EQ(st.distressed(), 1);

  st.Reset();
  EXPECT_EQ(st.distressed(), 0);
}


#endif /* STUDENT_TEST */
