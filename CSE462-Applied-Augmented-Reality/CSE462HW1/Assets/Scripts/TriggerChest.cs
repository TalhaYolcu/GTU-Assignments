using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerChest : MonoBehaviour
{

    public GameObject otherobj;
    // Start is called before the first frame update
    void Start()
    {
        otherobj.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnTriggerEnter(Collider other) {
        this.gameObject.SetActive(false);
        otherobj.SetActive(true);
    }
}
