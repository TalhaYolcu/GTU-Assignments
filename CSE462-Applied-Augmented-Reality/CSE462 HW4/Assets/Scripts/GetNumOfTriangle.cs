using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GetNumOfTriangle : MonoBehaviour
{

    public GameObject[] objects;
    private Vector2 look;
    private float mouseSensitivity=3f;
    private float movementSpeed=10f; 

    private Light[] lights;

    public Camera myCam;


   

    // Start is called before the first frame update
    void Start()
    {
        //checkTriangleCount();

        

        /*
        
        what is undone:


        in canvas, adjust objects positions
        in canvas adjust light sources positions and intensity

        all objects have lambertian material?



        */
               
    }

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

        //UpdateLook();
        //UpdateMovement();


    }

    void checkTriangleCount() {
        int totalTriangles = 0;
        foreach(MeshFilter mf in FindObjectsOfType(typeof(MeshFilter))){
            totalTriangles += mf.mesh.triangles.Length;
        }
        Debug.Log(totalTriangles);
        Debug.Log(UnityEditor.UnityStats.triangles);
    }




    

    


}
