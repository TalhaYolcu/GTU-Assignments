using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using MathNet.Numerics.LinearAlgebra.Factorization;
using MathNet.Numerics.LinearAlgebra.Double;
using Accord.Math;

public class Part1 : MonoBehaviour
{

    public double[,] Smatrix = new double[4, 2] { { 1, 2 }, { 5, 3 }, { 4, 10 }, { 1, 6 } };
    public double[,] Imatrix = new double[4, 2] { { 1, 2 }, { 5, 3 }, { 4, 10 }, { 1, 6 } };

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void part1() {

        SceneManager.LoadScene("Part1");

        print("Hi1");        


    }
    void print_1d_array(double[]matrix) {
        for (int i = 0; i < matrix.GetLength(0); i++){
            Debug.Log(" "+matrix[i]);
        }  
    }

    void print_matrix(double[,] matrix) {
        for (int i = 0; i < matrix.GetLength(0); i++){
            Debug.Log(i+": "+matrix[i,0]+" "+matrix[i,1]+" "+matrix[i,2]);
        }           
    }

    public void part1_1() {
        /*
        Write a C# function that given a set of point correspondences
        Si and Ii transponse calculates the corresponding homography matrix.
        You can assume that there are equal number of points for si and ıi
        and they are in correspondence. 
        This function should use a non-linear optimization method
        to calculate the homography.
        */        
        double[,] homography = calculateHomographyMatrixMatchGuaranteed(Smatrix,Imatrix);
        print("PART1.1");
        print_matrix(homography);
    }
    public void part1_2() {
        /*
        Write another C# function that does the same thing as 1.1.
        However, the list of points on the marker and the image
        are not guaranteed to match.This function will take another
        parameter as a matrix of numbers with entries ci,j indicating
        the degree of match between si and ıi        
        */
        double[,] homography = calculateHomographyMatrixMatchNotGuaranteed(Smatrix,Imatrix);
        print("PART1.2");
        print_matrix(homography);

    }
    public void part1_3() {
        /*
        Write another C# function that given a scene point xi yi and
        a homography matrix, calculates the projection of the given point
        onto the target image.
        */

        //calculated homography matrix
        double[,] homography = calculateHomographyMatrixMatchGuaranteed(Smatrix,Imatrix);

        double[,] xy = new double[3,1]{ { Smatrix[2,0] }, { Smatrix[2,1] } , { 1 } };

        double[,] projection = givenScenePointCalculateProjectionOntheTarget(homography,xy);
        print("PART1.3");
        print(projection[0,0]);
        print(projection[1,0]);
        print(projection[2,0]);

    }
    public void part1_4() {
        /*
        Write another C# function that given an image point uv and
        a homography matrix, calculates the projection of the given point
        onto the scene.
        */
        //calculated homography matrix
        double[,] homography = calculateHomographyMatrixMatchGuaranteed(Smatrix,Imatrix);

        double[,] uv = new double[3, 1] { { Imatrix[1, 0] }, {  Imatrix[1, 1] }, { 1 } };

        double[,] projection = givenImagePointCalculateProjectionOntotheScene(homography,uv);
        print("PART1.4");        
        print(projection[0,0]);
        print(projection[1,0]);
        print(projection[2,0]);       
    }
    public void part1_5() {
        /*
        You are to find at least five point correspondences
        in three images manually.
        Show the calculated matrices for each image using these point matches.
        Calculate the error for another 3 point matches you identify.
        Errors can be calculated as the Euclidean distance between
        the image of the point and the projected point.
        */

        //five points

        double[,] scenepoints=new double[5,2] { {0,700 }, { 100,600 }, { 200, 600 }, { 200, 500 }, { 0, 600} };

        double[,] imagepoint1=new double[5, 2] { { 535,356}, { 768,591 }, { 1000,597 }, { 999,826 } , { 535,588 } };

        double[,] imagepoint2=new double[5, 2] { { 447,500}, { 708, 756 }, { 954,761 }, {960, 1004 }, { 459,751 } };

        double[,] imagepoint3=new double[5,2] { { 720,300 }, { 947,545 }, { 1178,569}, {1169,785 }, {705,521 } };


   

        List<double[,]> xylist=new List<double[,]>(); //keeps x y 's
        List<double[,]> uvlist=new List<double[,]>(); //keeps u v 's

        double[,] hmatrix1=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint1);
        double[,] hmatrix2=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint2);
        double[,] hmatrix3=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint3);

        xylist.Add(new double[3,1] { { 0}, { 100 }, { 1 } });
        xylist.Add(new double[3,1] { { 100 }, { 100 }, { 1 } });
        xylist.Add(new double[3,1] { { 900 }, { 0 }, { 1 } });

        //First Image Projection
        uvlist.Add(new double[3, 1] { { 521 }, { 1743 }, { 1 } });
        uvlist.Add(new double[3, 1] { { 754 }, { 1744 }, { 1 } });
        uvlist.Add(new double[3, 1] { { 2615 }, { 1999 }, { 1 } });

        calculateMatchandError(1,hmatrix1,xylist,uvlist);

        uvlist=new List<double[,]>(); //clear uvlist

        //Second Image
        uvlist.Add(new double[3, 1] { { 501 }, { 1938}, { 1 } });
        uvlist.Add(new double[3, 1] { { 736 }, { 1941 }, { 1 } });
        uvlist.Add(new double[3, 1] { { 2609 }, { 2197}, { 1 } });

        calculateMatchandError(2,hmatrix2,xylist,uvlist);

        uvlist=new List<double[,]>(); //clear uvlist

        //Third Image
        uvlist.Add(new double[3, 1] { { 618 }, { 1699}, { 1 } });
        uvlist.Add(new double[3, 1] { { 876 }, { 1702}, { 1 } });
        uvlist.Add(new double[3, 1] { { 2680 }, { 1961 }, { 1 } });

        calculateMatchandError(3,hmatrix3,xylist,uvlist);
    }
    public void part1_6() {
        /*
        Find the projection of the following scene points onto the image.
            s1 = [7.5 5.5], s2 = [6.3 3.3] and s3 = [0.1 0.1].
        */

        double[,] scenepoints=new double[5,2] { {0,700 }, { 100,600 }, { 200, 600 }, { 200, 500 }, { 0, 600} };

        double[,] imagepoint1=new double[5, 2] { { 535,356}, { 768,591 }, { 1000,597 }, { 999,826 } , { 535,588 } };

        double[,] imagepoint2=new double[5, 2] { { 447,500}, { 708, 756 }, { 954,761 }, {960, 1004 }, { 459,751 } };

        double[,] imagepoint3=new double[5,2] { { 720,300 }, { 947,545 }, { 1178,569}, {1169,785 }, {705,521 } };

        List<double[,]> xylist=new List<double[,]>(); //keeps x y 's
        List<double[,]> uvlist=new List<double[,]>(); //keeps u v 's

        double[,] hmatrix1=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint1);
        double[,] hmatrix2=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint2);
        double[,] hmatrix3=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint3);

        double[,] sp1 = new double[3,1] { { 75 }, { 55 }, { 1 } };
        double[,] sp2 = new double[3,1] { { 63 }, { 33 }, { 1 } };
        double[,] sp3 = new double[3,1] { { 1 }, { 1 }, { 1 } };

        print("Projection of Image 1");
        double[,] projection1 = givenScenePointCalculateProjectionOntheTarget(hmatrix1,sp1);
        double[,] projection2 = givenScenePointCalculateProjectionOntheTarget(hmatrix1,sp2);
        double[,] projection3 = givenScenePointCalculateProjectionOntheTarget(hmatrix1,sp3);

        print_projection(sp1,projection1);
        print_projection(sp2,projection2);
        print_projection(sp3,projection3);
       
        print("Projection of Image 2");
        projection1 = givenScenePointCalculateProjectionOntheTarget(hmatrix2,sp1);
        projection2 = givenScenePointCalculateProjectionOntheTarget(hmatrix2,sp2);
        projection3 = givenScenePointCalculateProjectionOntheTarget(hmatrix2,sp3);

        print_projection(sp1,projection1);
        print_projection(sp2,projection2);
        print_projection(sp3,projection3);

        print("Projection of Image 3");
        projection1 = givenScenePointCalculateProjectionOntheTarget(hmatrix3,sp1);
        projection2 = givenScenePointCalculateProjectionOntheTarget(hmatrix3,sp2);
        projection3 = givenScenePointCalculateProjectionOntheTarget(hmatrix3,sp3);

        print_projection(sp1,projection1);
        print_projection(sp2,projection2);
        print_projection(sp3,projection3);

    }
    public void part1_7() {
        /*
        Find the projection of the following image points onto the scene.
            ı1 = [500 400], ı2 = [86 167] and ı3 = [10 10].
        */   

        double[,] scenepoints=new double[5,2] { {0,700 }, { 100,600 }, { 200, 600 }, { 200, 500 }, { 0, 600} };

        double[,] imagepoint1=new double[5, 2] { { 535,356}, { 768,591 }, { 1000,597 }, { 999,826 } , { 535,588 } };

        double[,] imagepoint2=new double[5, 2] { { 447,500}, { 708, 756 }, { 954,761 }, {960, 1004 }, { 459,751 } };

        double[,] imagepoint3=new double[5,2] { { 720,300 }, { 947,545 }, { 1178,569}, {1169,785 }, {705,521 } };

        List<double[,]> xylist=new List<double[,]>(); //keeps x y 's
        List<double[,]> uvlist=new List<double[,]>(); //keeps u v 's

        double[,] hmatrix1=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint1);
        double[,] hmatrix2=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint2);
        double[,] hmatrix3=calculateHomographyMatrixMatchGuaranteed(scenepoints,imagepoint3);

        double[,] ip1 = new double[3,1] { { 500 }, { 400 }, { 1 } };
        double[,] ip2 = new double[3,1] { { 86 }, { 167 }, { 1 } };
        double[,] ip3 = new double[3,1] { { 10 }, { 10 }, { 1 } };

        print("Inverse projection of Image 1");
        double[,] projection1 = givenImagePointCalculateProjectionOntotheScene(hmatrix1,ip1);
        double[,] projection2 = givenImagePointCalculateProjectionOntotheScene(hmatrix1,ip2);
        double[,] projection3 = givenImagePointCalculateProjectionOntotheScene(hmatrix1,ip3);

        print_projection(ip1,projection1);
        print_projection(ip2,projection2);
        print_projection(ip3,projection3);
       
        print("Inverse projection of Image 2");
        projection1 = givenImagePointCalculateProjectionOntotheScene(hmatrix2,ip1);
        projection2 = givenImagePointCalculateProjectionOntotheScene(hmatrix2,ip2);
        projection3 = givenImagePointCalculateProjectionOntotheScene(hmatrix2,ip3);

        print_projection(ip1,projection1);
        print_projection(ip2,projection2);
        print_projection(ip3,projection3);

        print("Inverse projection of Image 3");
        projection1 = givenImagePointCalculateProjectionOntotheScene(hmatrix3,ip1);
        projection2 = givenImagePointCalculateProjectionOntotheScene(hmatrix3,ip2);
        projection3 = givenImagePointCalculateProjectionOntotheScene(hmatrix3,ip3);

        print_projection(ip1,projection1);
        print_projection(ip2,projection2);
        print_projection(ip3,projection3);



    }   

    void print_projection(double[,]xy,double[,]match) {
        Debug.Log("Homography Calculating...");
        Debug.Log("(x,y) : " + xy[0, 0] + " , " + xy[1, 0] + " , " + xy[2, 0]);
        Debug.Log("(u,v) : " + match[0, 0] + " , " + match[1, 0] + " , " + match[2, 0]);        
    }

    void print_inverse_projection(double[,]uv,double[,] match) {
        Debug.Log("Inverse Homography Calculating...");
        Debug.Log("(u,v) : " + uv[0, 0] + " , " + uv[1, 0] + " , " + uv[2, 0]);
        Debug.Log("(x,y) : " + match[0, 0] + " , " + match[1, 0] + " , " + match[2, 0]);

    }

    void calculateMatchandError(int image_num,double[,] hmatrix1,List<double[,]> xylist,List<double[,]> uvlist) {
        print("Homography matrix for image "+image_num+":");
        print_matrix(hmatrix1);

        int i=0;
        foreach(double[,] xy in xylist) {
            double[,] uv = uvlist[i++];
            double[,] projection = givenScenePointCalculateProjectionOntheTarget(hmatrix1,xy);
            float projection_error = calculateProjectionError(projection,uv);
            print("Error percentage: "+projection_error);
        }        
    } 

    float calculateProjectionError(double[,] calculated,double[,] actual) {
        double x1 = calculated [0,0];
        double x2 = actual [0,0];

        double y1 = calculated [1,0];
        double y2 = actual [1,0];

        float calculatedDif = Mathf.Sqrt(Mathf.Pow((float)(x1), 2) + Mathf.Pow((float)(y1), 2));
        float actualDif = Mathf.Sqrt(Mathf.Pow((float)(x2), 2) + Mathf.Pow((float)(y2), 2));

        return Mathf.Abs((actualDif - calculatedDif) / actualDif * 100);

    }                


    double[,] createPmatrix(double[,] smatrix,double[,] imatrix,int N,int M) {
        double[,] pmatrix = new double[2 * N, M];
        int p = 0;
        for (int i = 0; i < 2 * N; i++){
            //fill the pmatrix with the needed values
            if (i % 2 == 0){
                pmatrix[i, 0] = -1 * smatrix[p, 0];
                pmatrix[i, 1] = -1 * smatrix[p, 1];
                pmatrix[i, 2] = -1;
                pmatrix[i, 3] = 0;
                pmatrix[i, 4] = 0;
                pmatrix[i, 5] = 0;
                pmatrix[i, 6] = smatrix[p, 0] * imatrix[p, 0];
                pmatrix[i, 7] = imatrix[p, 0] * smatrix[p, 1];
                pmatrix[i, 8] = imatrix[p, 0];
            }
            else{
                pmatrix[i, 0] = 0;
                pmatrix[i, 1] = 0;
                pmatrix[i, 2] = 0;
                pmatrix[i, 3] = -1 * smatrix[p, 0];
                pmatrix[i, 4] = -1 * smatrix[p, 1];
                pmatrix[i, 5] = -1;
                pmatrix[i, 6] = smatrix[p, 0] * imatrix[p, 1];
                pmatrix[i, 7] = imatrix[p, 1] * smatrix[p, 1];
                pmatrix[i, 8] = imatrix[p, 1];
                p++;
            }
        }    
        return pmatrix;    
    }

    double[] calculateHomography(double[,] smatrix,double[,] imatrix) {
        int N = smatrix.GetLength(0);
        int M = 9;
        double[,] pmatrix = createPmatrix(smatrix,imatrix,N,M);
        var mat = DenseMatrix.OfArray(pmatrix);
        var svd = mat.Svd(true);
        return svd.VT.Row(svd.VT.RowCount - 1).ToArray();        
    }

    double[,] calculateHomographyMatrixMatchGuaranteed(double[,] smatrix,double[,] imatrix) {

        double[] homography = calculateHomography(smatrix,imatrix);
        double[,] homographyMatrix = new double[3, 3];

        int row = 0;
        for (int i = 0; i < homography.Length; i++){
            if (i % 3 == 0 && i != 0) {
                ++row;
            }
            homographyMatrix[row, i % 3] = homography[i];
        }

        return homographyMatrix;
    } 
    double[,] calculateHomographyMatrixMatchNotGuaranteed(double[,] smatrix,double[,] imatrix) {
        double [,] result = new double[3,3];
        double[] homography = calculateHomography(smatrix,imatrix);
        double[,] homographyMatrix = new double[3, 3];

        int row = 0;
        for (int i = 0; i < homography.Length; i++)
        {
            if (i % 3 == 0 && i != 0) {
                ++row;
            }
            homographyMatrix[row, i % 3] = homography[i];
        }

        return homographyMatrix;
    }  
    double[,] givenScenePointCalculateProjectionOntheTarget(double[,] homography,double[,] xy) {
        double[,] projection = ApplyHomography(homography, xy);      
        return projection;
    }

    double[,] givenImagePointCalculateProjectionOntotheScene(double[,] homography,double[,] uv) {
        double[,] projection = ApplyInverseHomography(homography, uv);   
        return projection;
    }
    double[,] ApplyInverseHomography(double[,] homography, double[,] a){
        var m = DenseMatrix.OfArray(homography).Inverse();
        return ApplyHomography(m.ToArray(), a);
    }
    double [,] MultiplyMatrices(double[,] a, double[,] b) {
         return Accord.Math.Matrix.Dot(a,b);
    }
    double[,] ApplyHomography(double[,] homography, double[,] a){
        double[,] temp =MultiplyMatrices(homography, a);
        double[,] res = new double[,] { { temp[0, 0] / temp[2, 0] }, { temp[1, 0] / temp[2, 0] }, { 1 } };

        return res;
    }
    
}
