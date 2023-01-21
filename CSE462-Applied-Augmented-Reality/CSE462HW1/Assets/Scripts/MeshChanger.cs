using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;

public class MeshChanger : MonoBehaviour
{

    public GameObject obj;
    public Mesh cylinder;
    public Mesh sphere;
    public Mesh cube;

    public void redSelected() {
        obj.GetComponent<MeshRenderer>().material.color=Color.red;

    }
    public void blueSelected() {
        obj.GetComponent<MeshRenderer>().material.color=Color.blue;

    }
    public void cubeSelected() {
        obj.GetComponent<MeshFilter>().mesh=cube;
    }
    public void cylinderSelected() {
        obj.GetComponent<MeshFilter>().mesh=cylinder;        
    }
}
