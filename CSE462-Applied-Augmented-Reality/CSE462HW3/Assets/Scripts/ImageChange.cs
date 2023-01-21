using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using MathNet.Numerics.LinearAlgebra.Factorization;
using MathNet.Numerics.LinearAlgebra.Double;
using Accord.Math;

public class ImageChange : MonoBehaviour
{

    private int image_index=-1;
    private List<double[,]> xylist = new List<double[,]>();

    private double[,] refXYList =new double[4,2] { {478,2085} ,{2036,1605} , {1408,1941},{1367,2277}};
    private double[,] refUVList = new double[4,2] {{-64.174f,-22.556f},{22.48f,-4.22f},{-12.365f,-17.12f},{-14.6f,-29.89f}};

    private double[,] homography_matrix;
    public Sprite refImage;

    public List<Sprite> image_list=new List<Sprite>();

    public Canvas myCanvas;
    public Image image;

    public Button nextButton;

    public Button prevButton;
    public Text refText;

    public Transform augmentedObject;

    private UnityEngine.Vector3 initialTransform;

    // Start is called before the first frame update
    void Start()
    {

        xylist.Add(new double[3,1] { {1917},{1730},{1} });
        xylist.Add(new double[3,1] { {2128},{1629},{1} });
        xylist.Add(new double[3,1] { {2799},{1540},{1} });
        xylist.Add(new double[3,1] { {2918},{1622},{1} });
        xylist.Add(new double[3,1] { {2483},{1796},{1} });
        xylist.Add(new double[3,1] { {2513},{1826},{1} });

        xylist.Add(new double[3,1] { {2040},{1822},{1} });
        xylist.Add(new double[3,1] { {1857},{1786},{1} });
        xylist.Add(new double[3,1] { {1878},{1704},{1} });
        xylist.Add(new double[3,1] { {1959},{1588},{1} });
        xylist.Add(new double[3,1] { {2621},{2159},{1} });
        xylist.Add(new double[3,1] { {2327},{1570},{1} });

        xylist.Add(new double[3,1] { {1570},{1380},{1} });
        xylist.Add(new double[3,1] { {1906},{1482},{1} });
        xylist.Add(new double[3,1] { {2059},{1643},{1} });
        xylist.Add(new double[3,1] { {2163},{1495},{1} });
        xylist.Add(new double[3,1] { {2635},{1370},{1} });
        xylist.Add(new double[3,1] { {2209},{1639},{1} });  

       homography_matrix=calculateHomographyMatrix(refXYList,refUVList);   

       initialTransform=augmentedObject.transform.position;           

    }

    // Update is called once per frame
    void Update()
    {
        
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

    private double[,] calculateHomographyMatrix(double[,] smatrix,double[,] imatrix) {
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
    double [,] MultiplyMatrices(double[,] a, double[,] b) {
         return Accord.Math.Matrix.Dot(a,b);
    }    

    double[,] ApplyHomography(double[,] homography, double[,] a){
        double[,] temp =MultiplyMatrices(homography, a);
        double[,] res = new double[,] { { temp[0, 0] / temp[2, 0] }, { temp[1, 0] / temp[2, 0] }, { 1 } };

        return res;
    }    

    private double[,] calculateProjection(double[,] homography,double[,] xy) {
        double[,] projection = ApplyHomography(homography, xy);      
        return projection;        
    }

    private float calculateRotation(UnityEngine.Vector3 refObj,UnityEngine.Vector3 newObj) {
        return UnityEngine.Vector2.SignedAngle(refObj,newObj);
    }

    private float calculateScale(UnityEngine.Vector3 refObj,UnityEngine.Vector3 newObj) {
        float dist1=Mathf.Sqrt(Mathf.Pow(refObj.x,2)+Mathf.Pow(refObj.y,2));
        float dist2=Mathf.Sqrt(Mathf.Pow(newObj.x,2)+Mathf.Pow(newObj.y,2));
        float scale_ratio = dist2/dist1;
        return scale_ratio;

    }

    public void onNext() {

        if(image_index!=0) {
            refText.gameObject.SetActive(false);
        }

        if(image_index<17) {
            image_index++;
            image.sprite=image_list[image_index];
            double[,] projection = calculateProjection(homography_matrix,xylist[image_index]);
            augmentedObject.transform.position=new UnityEngine.Vector3((float)projection[0,0],(float)projection[1,0],86.38f);


        }
        else {
            nextButton.gameObject.SetActive(false);
        }



    }

    public void onPrev() {
        if(image_index<18) {
            nextButton.gameObject.SetActive(true);
        }
        if(image_index!=0) {
            refText.gameObject.SetActive(false);
        }        
        if(image_index==0) {
            image.sprite=refImage;
            refText.gameObject.SetActive(true);
            image_index--;
            augmentedObject.transform.position=initialTransform;


        }
        else if(image_index==-1) {
            //go to previous scene
            SceneManager.LoadScene("SampleScene");
        }
        else {
            image_index--;
            image.sprite=image_list[image_index];
            double[,] projection = calculateProjection(homography_matrix,xylist[image_index]);
            augmentedObject.transform.position =new UnityEngine.Vector3((float)projection[0,0],(float)projection[1,0],86.38f);
            

        }

    }
}
