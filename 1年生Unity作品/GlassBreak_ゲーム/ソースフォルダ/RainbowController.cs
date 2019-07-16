using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RainbowController : MonoBehaviour
{
    GameManager gameManager;

    public void DestroyEvent()
    {
        //ゲームマネージャの取得
        GameObject obj = GameObject.Find("gameManager");
        gameManager = obj.GetComponent<GameManager>();

        gameManager.AddDestroyRainbowCount();
    }
}
