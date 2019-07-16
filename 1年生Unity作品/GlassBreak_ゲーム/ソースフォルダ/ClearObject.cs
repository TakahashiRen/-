using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClearObject : MonoBehaviour
{
    GameManager gameManager;
    public int endTime;
    int timeCount;


    void Start ()
    {
        //ゲームマネージャの取得
        GameObject obj = GameObject.Find("gameManager");
        gameManager = obj.GetComponent<GameManager>();

        timeCount = 0;

    }


    void Update ()
    {
        //一定時間経ったらリザルト画面へ
        if (timeCount >= endTime)
        {
            gameManager.ChangeState(GameManager.StateId.end);
            Destroy(gameObject);
        }
        timeCount++;
    }
}
