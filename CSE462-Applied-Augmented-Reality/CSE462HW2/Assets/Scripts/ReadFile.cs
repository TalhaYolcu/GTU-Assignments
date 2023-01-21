using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using UnityEditor;
using System;
using Accord.Math.Decompositions;
using Accord;



public class ReadFile : MonoBehaviour{

    public Canvas myCanvas;
    public Material greenMat;
    public Camera myCam;
    private List<GameObject> blues=new List<GameObject>();
    private List<GameObject> yellows=new List<GameObject>();
    private List<Point3D> blue_points=new List<Point3D>();
    private List<Point3D> yellow_points=new List<Point3D>();
    private double error_rate=Double.MinValue;
    private double[,] rotation_error=new double[3,3];
    private double[,] tra_error=new double[3,1];
    private double[,] final_rotation=new double[3,3];
    private double[,] final_translation=new double[3,0];
    private bool move_enabled=false;
    private List<Vector3> differences=new List<Vector3>();
    private List<Vector3> final_calculated=new List<Vector3>();

    private Vector2 look;
    private float mouseSensitivity=3f;
    private float movementSpeed=10f;

    private void UpdateLook() {
        if(Input.GetAxis("Mouse ScrollWheel")>0) {
            myCam.fieldOfView--;
        }
        if(Input.GetAxis("Mouse ScrollWheel")<0) {
            myCam.fieldOfView++;
        }  
        look.x+=Input.GetAxis("Mouse X")*mouseSensitivity;
        look.y+=Input.GetAxis("Mouse Y")*mouseSensitivity;
        look.y=Mathf.Clamp(look.y,-89f,89f);
        myCam.transform.localRotation=Quaternion.Euler(-look.y,look.x,0);
    }
    private void UpdateMovement() {
        var x=Input.GetAxis("Horizontal");
        var y=Input.GetAxis("Vertical");
        var input = new Vector3();
        input+=myCam.transform.forward*y;
        input+=myCam.transform.right*x;
        input=Vector3.ClampMagnitude(input,1f);
        myCam.transform.Translate(input*movementSpeed*Time.deltaTime,Space.World);
    }
    private void Update() {

        UpdateLook();
        UpdateMovement();

        if(move_enabled) {
            for(int i=0;i<blues.Count;i++) {
                if(Vector3.Distance(yellows[i].transform.position,final_calculated[i])>=0.001f) {
                    float speed = 5f;
                    var step =  speed * Time.deltaTime; // calculate distance to move                    
                    yellows[i].transform.position=Vector3.MoveTowards(yellows[i].transform.position,final_calculated[i],step);
                }
            } 
        }
       
    }
    private void readFile(string path,bool color) {
        string[] lines=File.ReadAllLines(path);
        List<Point3D> points=new List<Point3D>();
        try {
            int number_of_line=Int32.Parse(lines[0]);
            for(int i=0;i<(number_of_line);i++){
                string[] floats=lines[i+1].Split(' ');
                float x1=float.Parse(floats[0]);
                float y1=float.Parse(floats[1]);
                float z1=float.Parse(floats[2]);
                points.Add(new Point3D(x1,y1,z1));

            }
            initializePoints(points,color);
        }   
        catch(FormatException) {
            throw new FormatException();
        }
    }
    private void initializePoints(List<Point3D> points,bool color) {
        for(int i=0;i<points.Count;i++) {
            GameObject mysphere=GameObject.CreatePrimitive(PrimitiveType.Sphere);
            mysphere.transform.position=new UnityEngine.Vector3(points[i].x,points[i].y,points[i].z);
            Color newCol = color ? Color.blue : Color.yellow;
            if(color) {
                blues.Add(mysphere);
                blue_points.Add(new Point3D(points[i].x,points[i].y,points[i].z));
            }
            else {
                yellows.Add(mysphere);
                yellow_points.Add(new Point3D(points[i].x,points[i].y,points[i].z));               
            }
            UnityEngine.Vector3 scale=new UnityEngine.Vector3(0.5f,0.5f,0.5f);
            mysphere.GetComponent<Renderer>().material.SetColor("_Color",newCol);
        }
    }

    private Point3D findCentroid(Point3D p1,Point3D p2,Point3D p3) {
        Point3D ret=new Point3D(0.0f,0.0f,0.0f);
        ret.x=(p1.x+p2.x+p3.x)/(3.0f);
        ret.y=(p1.y+p2.y+p3.y)/(3.0f);
        ret.z=(p1.z+p2.z+p3.z)/(3.0f);
        return ret;
    }
    private Point3D reCentrePoint(Point3D p1,Point3D center) {
        Point3D newp=new Point3D(0.0f,0.0f,0.0f);
        newp.x=p1.x-center.x;
        newp.y=p1.y-center.y;
        newp.z=p1.z-center.z;

        return newp;
    }
    private double[,] takeTransponse(double[,] matrix) {       
        return Accord.Math.Matrix.Transpose(matrix);
    }

    private double[,] matrixMultiply(double[,] matrixA,double[,] matrixB) {     
        return Accord.Math.Matrix.Dot(matrixA,matrixB);
    }

    private double matrixDet(double [,]arr1) {
        return Accord.Math.Matrix.Determinant(arr1);
    }
    private double[,] findTranslation(double[,] rotation,double[,] centreA,double[,] centreB) {
        double[,] multiplyRwithcentroidA=Accord.Math.Matrix.Dot(rotation,centreA);
        return Accord.Math.Elementwise.Subtract(centreB,multiplyRwithcentroidA);;

    }
    private bool tryTransformation(double[,] rotation,double[,] transformation) {
        bool break_flag=false;
        Point3D my_transform=new Point3D(0.0f,0.0f,0.0f);
        int match_count=0;
        double[,] final_rotation=new double[3,3];
        double[,] final_translation=new double[3,0];
        List<PointMatrix> blue_matrices=new List<PointMatrix>();
        List<PointMatrix> yellow_matrices=new List<PointMatrix>();
        List<PointMatrix> calculated_matrices=new List<PointMatrix>();

        for(int i=0;i<blues.Count;i++) {
            double[,] matrixA=new double[3,1];
            matrixA[0,0]=blues[i].transform.position.x;
            matrixA[1,0]=blues[i].transform.position.y;
            matrixA[2,0]=blues[i].transform.position.z;

            double[,] matrixB=new double[3,1];
            matrixB[0,0]=yellows[i].transform.position.x;
            matrixB[1,0]=yellows[i].transform.position.y;
            matrixB[2,0]=yellows[i].transform.position.z;

            blue_matrices.Add(new PointMatrix(matrixA));
            yellow_matrices.Add(new PointMatrix(matrixB));
            calculated_matrices.Add(new PointMatrix(Accord.Math.Elementwise.Add(Accord.Math.Matrix.Dot(rotation,matrixA),transformation)));
        }

        for(int i=0;i<yellow_matrices.Count;i++) {
            if(Convert.ToInt32(yellow_matrices[i].pmatrix[0,0])==Convert.ToInt32(calculated_matrices[i].pmatrix[0,0]) &&
               Convert.ToInt32(yellow_matrices[i].pmatrix[1,0])==Convert.ToInt32(calculated_matrices[i].pmatrix[1,0]) && 
               Convert.ToInt32(yellow_matrices[i].pmatrix[2,0])==Convert.ToInt32(calculated_matrices[i].pmatrix[2,0])
            ) {
                match_count++;
                if(match_count>=(blues.Count/2)) {
                    break;
                }
            }
        }
        if(match_count>=(blues.Count/2)) {
            break_flag=true;
        }
        double det=0;

        if(match_count<(blues.Count/2)) {
            for(int i=0;i<yellow_matrices.Count;i++) {
                double[,] error_matrix=new double[3,3];
                error_matrix[0,0]=calculated_matrices[i].pmatrix[0,0]-yellow_matrices[i].pmatrix[0,0];
                error_matrix[1,0]=calculated_matrices[i].pmatrix[1,0]-yellow_matrices[i].pmatrix[1,0];
                error_matrix[2,0]=calculated_matrices[i].pmatrix[2,0]-yellow_matrices[i].pmatrix[2,0];
                double temp_det=Accord.Math.Matrix.Determinant(error_matrix);
                det=det+temp_det*temp_det;
            }
        }
        if(error_rate<det) {
            error_rate=det;
            rotation_error=rotation;
            tra_error=transformation;
        }
        return break_flag;     
    }
    private bool tryTransformationGlobalScale(double[,]diagonal,double[,] rotation,double[,] transformation) {
        bool break_flag=false;
        Point3D my_transform=new Point3D(0.0f,0.0f,0.0f);
        int match_count=0;
        double[,] final_rotation=new double[3,3];
        double[,] final_translation=new double[3,0];
        List<PointMatrix> blue_matrices=new List<PointMatrix>();
        List<PointMatrix> yellow_matrices=new List<PointMatrix>();
        List<PointMatrix> calculated_matrices=new List<PointMatrix>();

        for(int i=0;i<blues.Count;i++) {
            double[,] matrixA=new double[3,1];
            matrixA[0,0]=blues[i].transform.position.x;
            matrixA[1,0]=blues[i].transform.position.y;
            matrixA[2,0]=blues[i].transform.position.z;

            double[,] matrixB=new double[3,1];
            matrixB[0,0]=yellows[i].transform.position.x;
            matrixB[1,0]=yellows[i].transform.position.y;
            matrixB[2,0]=yellows[i].transform.position.z;

            blue_matrices.Add(new PointMatrix(matrixA));
            yellow_matrices.Add(new PointMatrix(matrixB));
            calculated_matrices.Add(new PointMatrix(Accord.Math.Elementwise.Add(Accord.Math.Matrix.Dot(Accord.Math.Matrix.Dot(diagonal,rotation),matrixA),transformation)));
        }

        for(int i=0;i<yellow_matrices.Count;i++) {
            if(Convert.ToInt32(yellow_matrices[i].pmatrix[0,0])==Convert.ToInt32(calculated_matrices[i].pmatrix[0,0]) &&
               Convert.ToInt32(yellow_matrices[i].pmatrix[1,0])==Convert.ToInt32(calculated_matrices[i].pmatrix[1,0]) && 
               Convert.ToInt32(yellow_matrices[i].pmatrix[2,0])==Convert.ToInt32(calculated_matrices[i].pmatrix[2,0])
            ) {
                match_count++;
                if(match_count>=blues.Count) {
                    break;
                }
            }
        }
        if(match_count>=blues.Count) {
            break_flag=true;
            return break_flag;
        }
        double det=0;

        if(match_count<blues.Count) {
            for(int i=0;i<yellow_matrices.Count;i++) {
                double[,] error_matrix=new double[3,3];
                error_matrix[0,0]=calculated_matrices[i].pmatrix[0,0]-yellow_matrices[i].pmatrix[0,0];
                error_matrix[1,0]=calculated_matrices[i].pmatrix[1,0]-yellow_matrices[i].pmatrix[1,0];
                error_matrix[2,0]=calculated_matrices[i].pmatrix[2,0]-yellow_matrices[i].pmatrix[2,0];
                double temp_det=Accord.Math.Matrix.Determinant(error_matrix);
                det=det+temp_det*temp_det;
            }
        }
        if(error_rate<det) {
            error_rate=det;
            rotation_error=rotation;
            tra_error=transformation;
        }
        return break_flag;     
    }

    private void ransacTransform() {
        bool break_flag=false;
        Point3D my_transform=new Point3D(0.0f,0.0f,0.0f);

        for(int i=0;i<blues.Count && !break_flag;i++) {
            for(int j=0;j<blues.Count && !break_flag;j++) {
                if(j==i) {
                    break;
                }
                for(int k=0;k<blues.Count && !break_flag;k++) {
                    if(j==k || i==k) {
                        break;
                    }
                    for(int i2=0;i2<yellows.Count && !break_flag;i2++) {
                        for(int j2=0;j2<yellows.Count && !break_flag;j2++) {
                            if(i2==j2) {
                                break;
                            }
                            for(int k2=0;k2<yellows.Count && !break_flag;k2++) {
                                if(j2==k2 || i2==k2) {
                                    break;
                                }   

                                Point3D bp1=new Point3D(blues[i].transform.position.x,blues[i].transform.position.y,blues[i].transform.position.z);
                                Point3D bp2=new Point3D(blues[j].transform.position.x,blues[j].transform.position.y,blues[j].transform.position.z);
                                Point3D bp3=new Point3D(blues[k].transform.position.x,blues[k].transform.position.y,blues[k].transform.position.z);                                
                                Point3D yp1=new Point3D(yellows[i2].transform.position.x,yellows[i2].transform.position.y,yellows[i2].transform.position.z);
                                Point3D yp2=new Point3D(yellows[j2].transform.position.x,yellows[j2].transform.position.y,yellows[j2].transform.position.z);
                                Point3D yp3=new Point3D(yellows[k2].transform.position.x,yellows[k2].transform.position.y,yellows[k2].transform.position.z);

                                Point3D blue_centroid=findCentroid(bp1,bp2,bp3);
                                Point3D yellow_centroid=findCentroid(yp1,yp2,yp3);


                                bp1=reCentrePoint(bp1,blue_centroid);
                                bp2=reCentrePoint(bp2,blue_centroid);
                                bp3=reCentrePoint(bp3,blue_centroid);

                                yp1=reCentrePoint(yp1,yellow_centroid);
                                yp2=reCentrePoint(yp2,yellow_centroid);
                                yp3=reCentrePoint(yp3,yellow_centroid);

                                double[,] matrixA=new double[3,3];
                                double[,] matrixB=new double[3,3];
                                double[,] centroidmatrixA=new double[3,1];
                                double[,] centroidmatrixB=new double[3,1];
                                double[,] matrixH=new double[3,3];

                                matrixA[0,0]=bp1.x;
                                matrixA[0,1]=bp2.x;
                                matrixA[0,2]=bp3.x;

                                matrixA[1,0]=bp1.y;
                                matrixA[1,1]=bp2.y;
                                matrixA[1,2]=bp3.y;

                                matrixA[2,0]=bp1.z;
                                matrixA[2,1]=bp2.z;
                                matrixA[2,2]=bp3.z;      

                                matrixB[0,0]=yp1.x;
                                matrixB[0,1]=yp2.x;
                                matrixB[0,2]=yp3.x;

                                matrixB[1,0]=yp1.y;
                                matrixB[1,1]=yp2.y;
                                matrixB[1,2]=yp3.y;

                                matrixB[2,0]=yp1.z;
                                matrixB[2,1]=yp2.z;
                                matrixB[2,2]=yp3.z; 

                                centroidmatrixA[0,0]=blue_centroid.x;
                                centroidmatrixA[1,0]=blue_centroid.y;
                                centroidmatrixA[2,0]=blue_centroid.z;

                                centroidmatrixB[0,0]=yellow_centroid.x;
                                centroidmatrixB[1,0]=yellow_centroid.y;
                                centroidmatrixB[2,0]=yellow_centroid.z;

                                double[,] transponsesubtractedmatrixB=takeTransponse(matrixB);

                                matrixH=matrixMultiply(matrixA,transponsesubtractedmatrixB);

                                SingularValueDecomposition svd=new SingularValueDecomposition(matrixH,true,true);
                                
                                double[,] vmatrix=svd.RightSingularVectors;
                                double[,] umatrix=svd.LeftSingularVectors;

                                double[,] rotation=matrixMultiply(vmatrix,takeTransponse(umatrix));

                                if(matrixDet(rotation)<0) {
                                    svd=new SingularValueDecomposition(rotation,true,true);
                                    vmatrix=svd.RightSingularVectors;
                                    umatrix=svd.LeftSingularVectors;
                                    for(int mm=0;mm<3;mm++) {
                                        vmatrix[mm,2]=vmatrix[mm,2]*(-1.0);
                                    }
                                    rotation=matrixMultiply(vmatrix,takeTransponse(umatrix));
                                }
                                double[,] translation=findTranslation(rotation,centroidmatrixA,centroidmatrixB);
                              
                                break_flag=tryTransformation(rotation,translation);

                                if(break_flag) {
                                    final_rotation=rotation;
                                    final_translation=translation;                                   
                                    return;
                                }                                
                            }

                        }
                    }
                }
            }
        }     
        if(!break_flag) {
            final_rotation=rotation_error;
            final_translation=tra_error;
        }    
    }  

    private void ransacTransformGlobalScale() {
        bool break_flag=false;
        Point3D my_transform=new Point3D(0.0f,0.0f,0.0f);

        for(int i=0;i<blues.Count && !break_flag;i++) {
            for(int j=0;j<blues.Count && !break_flag;j++) {
                if(j==i) {
                    break;
                }
                for(int k=0;k<blues.Count && !break_flag;k++) {
                    if(j==k || i==k) {
                        break;
                    }
                    for(int i2=0;i2<yellows.Count && !break_flag;i2++) {
                        for(int j2=0;j2<yellows.Count && !break_flag;j2++) {
                            if(i2==j2) {
                                break;
                            }
                            for(int k2=0;k2<yellows.Count && !break_flag;k2++) {
                                if(j2==k2 || i2==k2) {
                                    break;
                                }   

                                Point3D bp1=new Point3D(blues[i].transform.position.x,blues[i].transform.position.y,blues[i].transform.position.z);
                                Point3D bp2=new Point3D(blues[j].transform.position.x,blues[j].transform.position.y,blues[j].transform.position.z);
                                Point3D bp3=new Point3D(blues[k].transform.position.x,blues[k].transform.position.y,blues[k].transform.position.z);                                
                                Point3D yp1=new Point3D(yellows[i2].transform.position.x,yellows[i2].transform.position.y,yellows[i2].transform.position.z);
                                Point3D yp2=new Point3D(yellows[j2].transform.position.x,yellows[j2].transform.position.y,yellows[j2].transform.position.z);
                                Point3D yp3=new Point3D(yellows[k2].transform.position.x,yellows[k2].transform.position.y,yellows[k2].transform.position.z);

                                Point3D blue_centroid=findCentroid(bp1,bp2,bp3);
                                Point3D yellow_centroid=findCentroid(yp1,yp2,yp3);


                                bp1=reCentrePoint(bp1,blue_centroid);
                                bp2=reCentrePoint(bp2,blue_centroid);
                                bp3=reCentrePoint(bp3,blue_centroid);

                                yp1=reCentrePoint(yp1,yellow_centroid);
                                yp2=reCentrePoint(yp2,yellow_centroid);
                                yp3=reCentrePoint(yp3,yellow_centroid);

                                double[,] matrixA=new double[3,3];
                                double[,] matrixB=new double[3,3];
                                double[,] centroidmatrixA=new double[3,1];
                                double[,] centroidmatrixB=new double[3,1];
                                double[,] matrixH=new double[3,3];

                                matrixA[0,0]=bp1.x;
                                matrixA[0,1]=bp2.x;
                                matrixA[0,2]=bp3.x;

                                matrixA[1,0]=bp1.y;
                                matrixA[1,1]=bp2.y;
                                matrixA[1,2]=bp3.y;

                                matrixA[2,0]=bp1.z;
                                matrixA[2,1]=bp2.z;
                                matrixA[2,2]=bp3.z;      

                                matrixB[0,0]=yp1.x;
                                matrixB[0,1]=yp2.x;
                                matrixB[0,2]=yp3.x;

                                matrixB[1,0]=yp1.y;
                                matrixB[1,1]=yp2.y;
                                matrixB[1,2]=yp3.y;

                                matrixB[2,0]=yp1.z;
                                matrixB[2,1]=yp2.z;
                                matrixB[2,2]=yp3.z; 

                                centroidmatrixA[0,0]=blue_centroid.x;
                                centroidmatrixA[1,0]=blue_centroid.y;
                                centroidmatrixA[2,0]=blue_centroid.z;

                                centroidmatrixB[0,0]=yellow_centroid.x;
                                centroidmatrixB[1,0]=yellow_centroid.y;
                                centroidmatrixB[2,0]=yellow_centroid.z;

                                double[,] transponsesubtractedmatrixB=takeTransponse(matrixB);

                                matrixH=matrixMultiply(matrixA,transponsesubtractedmatrixB);

                                SingularValueDecomposition svd=new SingularValueDecomposition(matrixH,true,true);
                                
                                double[,] vmatrix=svd.RightSingularVectors;
                                double[,] umatrix=svd.LeftSingularVectors;

                                double[,] rotation=matrixMultiply(vmatrix,takeTransponse(umatrix));

                                if(matrixDet(rotation)<0) {
                                    svd=new SingularValueDecomposition(rotation,true,true);
                                    vmatrix=svd.RightSingularVectors;
                                    umatrix=svd.LeftSingularVectors;
                                    for(int mm=0;mm<3;mm++) {
                                        vmatrix[mm,2]=vmatrix[mm,2]*(-1.0);
                                    }
                                    rotation=matrixMultiply(vmatrix,takeTransponse(umatrix));
                                }
                                rotation=matrixMultiply(svd.DiagonalMatrix,rotation);
                                double[,] translation=findTranslation(rotation,centroidmatrixA,centroidmatrixB);
                                double[,] ss=svd.DiagonalMatrix;
/*
                                double[,] ss=Accord.Math.Matrix.Dot(Accord.Math.Matrix.Dot(Accord.Math.Matrix.Inverse(svd.LeftSingularVectors),matrixH),Accord.Math.Matrix.Inverse(Accord.Math.Matrix.Transpose(svd.RightSingularVectors)));
                                /*print(ss[0,0]+" "+ss[0,1]+" "+ss[0,2]);
                                print(ss[1,0]+" "+ss[1,1]+" "+ss[1,2]);
                                print(ss[2,0]+" "+ss[2,1]+" "+ss[2,2]);
                                return;
*/                         

                                break_flag=tryTransformationGlobalScale(ss,rotation,translation);

                                if(break_flag) {
                                    final_rotation=rotation;
                                    final_translation=translation;                                   
                                    return;
                                }                                
                            }

                        }
                    }
                }
            }
        }     
        if(!break_flag) {
            final_rotation=rotation_error;
            final_translation=tra_error;
        }    
    }

    private void makeMovement() {
        List<PointMatrix> blue_matrices=new List<PointMatrix>();
        List<PointMatrix> calculated_matrices=new List<PointMatrix>();

        for(int i=0;i<blues.Count;i++) {
            double[,] matrixA=new double[3,1];
            matrixA[0,0]=blues[i].transform.position.x;
            matrixA[1,0]=blues[i].transform.position.y;
            matrixA[2,0]=blues[i].transform.position.z;

            blue_matrices.Add(new PointMatrix(matrixA));
            calculated_matrices.Add(new PointMatrix(Accord.Math.Elementwise.Add(Accord.Math.Matrix.Dot(final_rotation,matrixA),final_translation)));
            final_calculated.Add(new Vector3((float)calculated_matrices[i].pmatrix[0,0],(float)calculated_matrices[i].pmatrix[1,0],(float)calculated_matrices[i].pmatrix[2,0]));
            yellows[i].AddComponent<LineRenderer>();
            LineRenderer lineRenderer=yellows[i].GetComponent<LineRenderer>();
            lineRenderer.positionCount=2;
            lineRenderer.SetPosition(0,yellows[i].transform.position);
            lineRenderer.SetPosition(1,final_calculated[i]);
            lineRenderer.startColor=Color.green;
            lineRenderer.endColor=Color.green;
            lineRenderer.colorGradient=new Gradient();
            lineRenderer.material=greenMat;
        }

        for(int i=0;i<blues.Count;i++) {
            float calculatedX=(float)(calculated_matrices[i].pmatrix[0,0]-yellow_points[i].x);
            float calculatedY=(float)(calculated_matrices[i].pmatrix[1,0]-yellow_points[i].y);
            float calculatedZ=(float)(calculated_matrices[i].pmatrix[2,0]-yellow_points[i].z);
            differences.Add(new Vector3(calculatedX,calculatedY,calculatedZ));
        } 
    }  

    public void onMode1() {

        try {
            var path1=EditorUtility.OpenFilePanel("Select first file",Application.dataPath,"");
            readFile(path1,true); //blue
            
            var path2=EditorUtility.OpenFilePanel("Select second file",Application.dataPath,"");
            readFile(path2,false); //yellow

            myCanvas.enabled=false;
            AssetDatabase.Refresh();
            ransacTransform();

/*
            print(final_rotation[0,0]+" "+final_rotation[0,1]+" "+final_rotation[0,2]+" ");
            print(final_rotation[1,0]+" "+final_rotation[1,1]+" "+final_rotation[1,2]+" ");
            print(final_rotation[2,0]+" "+final_rotation[2,1]+" "+final_rotation[2,2]+" ");
            print(final_translation[0,0]+" "+final_translation[1,0]+" "+final_translation[2,0]); 
*/          

            makeMovement();
            move_enabled=true;
        }
        catch(FormatException) {
            print("Exception occured in parse");
        }
    }

    public void onMode2() {
        try {
            var path1=EditorUtility.OpenFilePanel("Select first file",Application.dataPath,"");
            readFile(path1,true); //blue
            
            var path2=EditorUtility.OpenFilePanel("Select second file",Application.dataPath,"");
            readFile(path2,false); //yellow

            myCanvas.enabled=false;
            AssetDatabase.Refresh();

            ransacTransformGlobalScale();

/*
            print(final_rotation[0,0]+" "+final_rotation[0,1]+" "+final_rotation[0,2]+" ");
            print(final_rotation[1,0]+" "+final_rotation[1,1]+" "+final_rotation[1,2]+" ");
            print(final_rotation[2,0]+" "+final_rotation[2,1]+" "+final_rotation[2,2]+" ");
            print(final_translation[0,0]+" "+final_translation[1,0]+" "+final_translation[2,0]); 
*/          

            makeMovement();
            move_enabled=true;            
        }
        catch(FormatException) {
            print("Exception occured in parse");
        }
    }
    
}

public class PointMatrix {
    public double[,] pmatrix=new double[3,1];

    public PointMatrix(double[,] mat) {
        for(int i=0;i<3;i++) {
            pmatrix[i,0]=mat[i,0];
        }
    }
}

public class Point3D{
    public float x;
    public float y;
    public float z;

    public Point3D(float x1,float y1,float z1) {
        x=x1;y=y1;z=z1;
    }
    public bool compare(Point3D p1){
        bool comparison = false;
        if(p1.x==this.x && p1.y==this.y && p1.z==this.z) {
            comparison=true;
        }
        return comparison;
    }
}

