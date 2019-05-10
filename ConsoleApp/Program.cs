using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Drawing;
using System.Diagnostics;

using CompetitiveCode;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Stopwatch st = new Stopwatch();

            string path = "D:\\palmprint_database\\cut_polyU";

            int numPalms = 10;
            int numImages = 100;

            float[,] distMat = new float[numImages, numImages]; // should be read in Matlab using 'float32' precision
            Bitmap[] images = new Bitmap[numImages];
            int cnt = 0;

            // read all images
            for(int i=1;i<= numPalms; i++)
            {
                for(int j=1;j<=50;j++)
                {
                    string fileName = path + string.Format("\\{0:D4}_{1:D2}.bmp",i,j);
                    FileInfo f = new FileInfo(fileName);

                    if(f.Exists)
                    {
                        images[cnt] = (Bitmap)Bitmap.FromFile(f.FullName);
                        cnt++;
                    }
                }
            }

            // feature extract and match
            //FeatureExtractor extractor = new FeatureExtractor();
            FeatureMatcher matcher = new FeatureMatcher();

            for (int i=0;i< numImages; i++)
            {
                Console.WriteLine(string.Format("Matching person {0}...",i));

                float[] distVect = new float[numImages];
                st.Start();
                for(int j=i+1;j< numImages; j++)
                {
                    distMat[i, j] = (float)matcher.Match(images[i], images[j]);
                    distMat[j, i] = distMat[i, j];

                    distVect[j] = (float)matcher.Match(images[i], images[j]);
                }
                st.Stop();
                System.Console.WriteLine(string.Format("Person {0} used {1} seconds.",i,(double)st.ElapsedMilliseconds / 1000));
                st.Reset();

                using (FileStream fs = new FileStream(string.Format("{0}.sim", i), FileMode.OpenOrCreate, FileAccess.ReadWrite))
                {
                    BinaryWriter w = new BinaryWriter(fs);

                    for (int j = 0; j < numImages; j++)
                    {
                        w.Write(distVect[j]);
                    }

                    w.Close();
                }
            }

            matcher.Dispose();

            // write distances
            using (FileStream fs = new FileStream("similarity.sim", FileMode.OpenOrCreate, FileAccess.ReadWrite))
            {
                BinaryWriter w = new BinaryWriter(fs); 

                for (int i = 0; i < numImages; i++)
                {
                    for (int j = 0; j < numImages; j++)
                    {
                        w.Write(distMat[i, j]);
                    }
                }

                w.Close();
            }
        }
    }
}
