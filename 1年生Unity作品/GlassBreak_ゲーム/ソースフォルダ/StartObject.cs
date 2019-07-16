/*
    GF3_11_高橋蓮
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartObject : MonoBehaviour
{
    GameManager gameManager;
    public int startTime;
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
        //一定時間経ったらゲームスタート
        if(timeCount >= startTime)
        {
            gameManager.ChangeState(GameManager.StateId.play);
            Destroy(gameObject);
        }
        timeCount++;
	}
}
