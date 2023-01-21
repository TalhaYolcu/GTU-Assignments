/*using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ChestGameStarter : MonoBehaviour{
    private bool isSelected=false;
    private GameObject selectedObject;
    private bool touchneeded=false;
    private Quaternion initialRotCam;
    private bool gamefinished=false;
    public GameObject lbutton;
    public GameObject rbutton;
    public GameObject okbutton;
    public GameObject backbutton;
    public Text text;
    public GameObject[] chests;
    public Camera mainCam;
    private int generate_random() {
        float num=Random.Range(1.0f,4.0f);
        return (int)num*90;
    }
    // Start is called before the first frame update
    void Start(){
        initialRotCam=mainCam.transform.rotation;
        foreach(GameObject obj in chests) {
            float z=(float)generate_random();
            obj.transform.Rotate(0,0,z);
        }
        GameObject.Find("LButton").SetActive(false);
        GameObject.Find("RButton").SetActive(false);
        GameObject.Find("OKButton").SetActive(false);
        GameObject.Find("BackButton").SetActive(false);
        touchneeded=true;

    }

    // Update is called once per frame
    void Update(){
        if(touchneeded && !gamefinished && !isSelected) {
            okbutton.SetActive(false);
        }
        if(Input.GetMouseButtonDown(0) && touchneeded) {
            Ray ray= Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit _hitinfo;
            if(Physics.Raycast(ray,out _hitinfo)) {
                var col=_hitinfo.transform.GetComponent<Collider>();
                if(col!=null) {
                    isSelected=true;
                    selectedObject=_hitinfo.transform.gameObject;
                    OnSelected();
                }
            } 
        }
        if(selectedObject!=null && !touchneeded) {
            int angle=(int)selectedObject.transform.localRotation.eulerAngles.y;
            if(angle==270) {
                okbutton.SetActive(true);
            }
        }
        bool check_flag=true;
        foreach(GameObject ch in chests) {
            if(ch.transform.localRotation.eulerAngles.y!=270) {
                check_flag=false;
                break;
            }
        }
        if(check_flag) {
            gamefinished=true;
            text.text="Game is finished, returning back to the previous scene";
            SceneManager.LoadScene("SixthGroupScene");
        }
    }

    void OnSelected() {
        touchneeded=false;
        int angle=(int)selectedObject.transform.localRotation.eulerAngles.y;
        if(angle<270) {
            if(selectedObject.name.Contains("chest_1")) {
                lbutton.SetActive(true);
                rbutton.SetActive(true);
                backbutton.SetActive(true);
                mainCam.transform.position=new Vector3(-8.5f,2,-18);
                mainCam.transform.rotation=new Quaternion(0.0f,0.0f,0.0f,0.0f);
            } 
            else if(selectedObject.name.Contains("chest_2")) {
                lbutton.SetActive(true);
                rbutton.SetActive(true);
                backbutton.SetActive(true);                
                mainCam.transform.position=new Vector3(-0.5f,2,-18);
                mainCam.transform.rotation=new Quaternion(0.0f,0.0f,0.0f,0.0f);

            }
            else if(selectedObject.name.Contains("chest_3")) {
                lbutton.SetActive(true);
                rbutton.SetActive(true);
                backbutton.SetActive(true);                
                mainCam.transform.position=new Vector3(8.5f,2,-18);
                mainCam.transform.rotation=new Quaternion(0.0f,0.0f,0.0f,0.0f);
            } 
        }
        else {
            touchneeded=true;
            isSelected=false;
        }

    }
    public void OnLeft() {
        int angle=(int)selectedObject.transform.localRotation.eulerAngles.y;
        selectedObject.transform.Rotate(new Vector3(0.0f,0.0f,90.0f));     
    }
    public void OnRight() {
        int angle=(int)selectedObject.transform.localRotation.eulerAngles.y;
        selectedObject.transform.Rotate(new Vector3(0.0f,0.0f,-90.0f));      
    }
    public void OnBack() {
        mainCam.transform.position=new Vector3(0.0f,14.97f,-27.98f);
        mainCam.transform.rotation=initialRotCam;
        touchneeded=true;
        isSelected=false;
    }
    public void OnOk() {
        mainCam.transform.position=new Vector3(0.0f,14.97f,-27.98f);
        mainCam.transform.rotation=initialRotCam;
        touchneeded=true;
        isSelected=false;
    }
}
*/