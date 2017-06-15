#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(){
    Mat image = imread("C:/image.jpg");
    int HistR[257] = {0};
    int HistG[257] = {0};
    int HistB[257] = {0};
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++)
        {
            Vec3b intensity = image.at<Vec3b>(Point(j, i));
            int Red = intensity.val[0];
            int Green = intensity.val[1];
            int Blue = intensity.val[2];
            HistR[Red] = HistR[Red]+1;
            HistB[Blue] = HistB[Blue]+1;
            HistG[Green] = HistG[Green]+1;
        }
    Mat HistPlotR (500, 256, CV_8UC3, Scalar(0, 0, 0));
    Mat HistPlotG (500, 256, CV_8UC3, Scalar(0, 0, 0));
    Mat HistPlotB (500, 256, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < 256; i=i+2)
    {
        line(HistPlotR, Point(i, 500), Point(i, 500-HistR[i]), Scalar(0, 0, 255),1,8,0);
        line(HistPlotG, Point(i, 500), Point(i, 500-HistG[i]), Scalar(0, 255, 0),1,8,0);
        line(HistPlotB, Point(i, 500), Point(i, 500-HistB[i]), Scalar(255, 0, 0),1,8,0);
    }
    namedWindow("Red Histogram");
    namedWindow("Green Histogram");
    namedWindow("Blue Histogram");
    imshow("Red Histogram", HistPlotR);
    imshow("Green Histogram", HistPlotG);
    imshow("Blue Histogram", HistPlotB);
    waitKey(0);
    return 0;
}
/*
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity ADDER is 
  generic( WIDTH : positive := 8 );
  port( CIN  : in  std_logic;
        A    : in  std_logic_vector(WIDTH-1 downto 0);
        B    : in  std_logic_vector(WIDTH-1 downto 0);
        F    : out std_logic_vector(WIDTH-1 downto 0);
        COUT : out std_logic);
end entity ADDER;

-- Ripple Carry Adder
architecture RCA of ADDER is 
  signal CIN0 : unsigned(0 downto 0);
  signal FIN  : unsigned(WIDTH downto 0);
begin
  CIN0(0) <= CIN;
  FIN <= resize(unsigned(A), WIDTH+1) + resize(unsigned(B), WIDTH+1) + CIN0; -- yes, I know it's not a ripple carry adder
  F    <= std_logic_vector(FIN(WIDTH-1 downto 0));
  COUT <= FIN(WIDTH);
end architecture RCA;

-- Carry Select Adder
architecture CSA of ADDER is
  component ADDER is 
    generic( WIDTH : positive );
    port( CIN  : in  std_logic;
          A    : in  std_logic_vector(WIDTH-1 downto 0);
          B    : in  std_logic_vector(WIDTH-1 downto 0);
          F    : out std_logic_vector(WIDTH-1 downto 0);
          COUT : out std_logic);
  end component ADDER;
  signal F0, F1       : std_logic_vector(WIDTH-1 downto 0);
  signal COUT0, COUT1 : std_logic;
begin
  ADD0: ADDER generic map( WIDTH => WIDTH)
    port map ( 
          CIN  => '0'  ,
          A    => A    ,
          B    => B    ,
          F    => F0    ,
          COUT => COUT0 );
  ADD1: ADDER generic map( WIDTH => WIDTH)
    port map ( 
          CIN  => '1'  ,
          A    => A    ,
          B    => B    ,
          F    => F1    ,
          COUT => COUT1 );
  COUT <= COUT1 when CIN = '1' else COUT0;
  F    <= F1    when CIN = '1' else F0;
end architecture CSA;

-- here's the configuration
configuration CSAC of ADDER is
  for CSA
    for all: ADDER
      use entity work.ADDER(RCA);
    end for;
  end for;
end configuration CSAC;

*/