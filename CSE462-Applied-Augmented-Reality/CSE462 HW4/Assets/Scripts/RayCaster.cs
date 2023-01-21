using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEngine.UI;
using System.IO;

public class RayCaster : MonoBehaviour
{

    //all objects in the scene
    public GameObject[] objects;

    //our reference camera
    public Camera cam;

    // Adjustable camera parameters
    public int imageWidth = 640;
    public int imageHeight = 480;
    public float fov=100;
    public float aspectRatio=1.33f;

    //all light sources
    public Light[] lightSources;

    //all possible hits for blackhole mode
    public bool[,] allHits=new bool[640,480];

    //all possible rays for blackhole mode
    public Ray[,] allRays=new Ray[640,480];

    //blackhole mode
    public bool blackhole=true;

    // References to the RawImage UI element
    public RawImage image;

    private Texture2D texture;

    //blackhole object
    public GameObject myBlackHole;

    void Start()
    {
        //init texture and image
        texture = new Texture2D(640, 480);
        image.texture = texture;
        checkTriangleCount();


        //black hole mode off
        if(!blackhole) {
            //run normal raycasting
            withoutBlackHole();
        }
        else {
            //black hole mode on, first initialize rays and possible hits
            for (int i=0;i<imageWidth; i++){
                for(int j = 0; j < imageHeight; j++){
                    allRays[i,j]=cam.ViewportPointToRay(new Vector3((float)i/imageWidth, (float)j/imageHeight, 0));
                    allHits[i,j]=false;
                }
            }            
        }
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        //if black hole mode is no, then send rays to create frame
        if(blackhole) {
            if(withBlackHole()) {
                createImageFile("_with_black_hole");
                blackhole=false;
            }  
        }
    }
    private bool withBlackHole() {
        bool Finito=true;
        for (int x = 0; x < imageWidth; x++){
            for (int y = 0; y < imageHeight; y++){
                //if there is no hit in that pixel
                if (!allHits[x,y]){
                    RaycastHit hit;
                    //send ray
                    if (Physics.Raycast(allRays[x,y], out hit,1)){
                        //hit
                        allHits[x,y]=true;
                        int hitCount=0;
                        Color color= hit.collider.GetComponent<Renderer>().material.color;
                        for (int k = 0; k < 3; k++){   
                            hitCount+=sendRay(lightSources[k],hit.point);
                        }
                        Color newColor= new Color(hitCount*(color.r/3),hitCount*(color.g/3),hitCount*(color.b/3));
                        texture.SetPixel(x, y,newColor);
                    }
                    else{
                        Finito=false;
                        allRays[x,y].origin=allRays[x,y].origin+(allRays[x,y].direction.normalized);
                        Vector3 newDirection=(myBlackHole.transform.position-allRays[x,y].origin);
                        Vector3 dir=newDirection.normalized+ (allRays[x,y].direction);
                        allRays[x,y].direction=dir.normalized;
                    }
                }
            }
        }
        texture.Apply();
        return Finito;
    }
    private void withoutBlackHole() {
        //in x coordinates
        for (int i=0;i<imageWidth; i++)
        {
            //in y coordinates
            for(int j = 0; j < imageHeight; j++)
            {
                //camera sends a ray to the direction
                Ray ray=cam.ViewportPointToRay(new Vector3((float)i/imageWidth, (float)j/imageHeight, 0));
                
                //there is a hit on that ray
                RaycastHit hit;
                if (Physics.Raycast(ray, out hit, Mathf.Infinity))
                {
                    //lights will send the rays to that hit point
                    int hitCount=0;
                    Vector3 hitP=hit.point;
                    //get color the change the color intensity
                    Color newColor=hit.collider.GetComponent<Renderer>().material.color;
                    //each light sends a ray to the pointa
                    foreach(Light myLight in lightSources) {
                        hitCount+=sendRay(myLight,hitP);
                    }
                    //ratio the color and hitcount depend on the light source count
                    newColor.r=(newColor.r*hitCount)/3;
                    newColor.g=(newColor.g*hitCount)/3;
                    newColor.b=(newColor.b*hitCount)/3;

                    //set the pixel color
                    texture.SetPixel(i, j, newColor);
                }
                else
                {
                    texture.SetPixel(i,j,Color.black);
                }
            }
        }
        //apply texture, ray casting is done
        texture.Apply();

        createImageFile("_without_black_hole");
    }

    private void createImageFile(string s) {
        //if directory does not exists, create it
        if(!Directory.Exists(Application.dataPath+"/GeneratedImages")) {
            Directory.CreateDirectory(Application.dataPath+"/GeneratedImages");
        }

        //refresh database
        AssetDatabase.Refresh();

        //take filepath
        string filePath = Application.dataPath+"/GeneratedImages/image"+s+".png";

        // Encode the texture into a .png file
        byte[] bytes = texture.EncodeToPNG();

        // Create a new file at the specified location, overwriting any file with the same name
        FileStream fileStream = File.Create(filePath);

        // Write the .png file to the file stream
        fileStream.Write(bytes, 0, bytes.Length);

        // Close the file stream
        fileStream.Close();        

        //refresh database
        AssetDatabase.Refresh();

        Debug.Log("Image is generated");        
    }


    private int sendRay(Light light,Vector3 hitP) {

        RaycastHit hit;
        int hit_flag=0;
        //take direction
        Vector3 dir = hitP-light.transform.position;
        dir.Normalize();
        Ray ray = new Ray(light.transform.position,dir);
        if (Physics.Raycast(ray , out hit, Mathf.Infinity)){
            if(Vector3.Distance(hit.point,hitP)<=0.001) {
                hit_flag=1;
            }
            if(hit.point==hitP) {
                hit_flag=1;
            }
        }        
        return hit_flag;
    }

    private void checkTriangleCount() {

        //cube 12 triangle
        //capsule 832
        //cylinder 80
        //plane 200
        //sphere 768
        int totalTrianglecount=0;
        foreach(GameObject obj in objects) {
            if(obj.GetComponent<MeshFilter>().sharedMesh.name.Equals("Cube")) {
                totalTrianglecount+=12;
            }
            else if(obj.GetComponent<MeshFilter>().sharedMesh.name.Equals("Capsule")) {
                totalTrianglecount+=832;
            }
            else if(obj.GetComponent<MeshFilter>().sharedMesh.name.Equals("Cylinder")) {
                totalTrianglecount+=80;
            }
            else if(obj.GetComponent<MeshFilter>().sharedMesh.name.Equals("Sphere")) {
                totalTrianglecount+=768;
            }                        
        }
        Debug.Log("Calculated triangle Count = "+totalTrianglecount);

        int totalTriangles = 0;
        foreach(MeshFilter mf in FindObjectsOfType(typeof(MeshFilter))){
            totalTriangles += mf.mesh.triangles.Length;
        }
        Debug.Log("Other triangle Counts?="+totalTriangles);
        Debug.Log("Other triangle Counts?="+UnityEditor.UnityStats.triangles);        
    }
    
}



