using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RainbowGenerator : MonoBehaviour
{
    public int generateNum = 0;            //生成するボールの数 
    public int generateTime = 0;           //生成する間隔　(秒)
    public bool generated = false;          //生成が終わったか
    private int generateCount = 0;          //生成したボールの数
    private int timeCount = 0;              //時間のカウント
    BallGenerator ballGenerator;              //ボールジェネレータースクリプト
    GameManager gameManager;                //ゲームマネージャスクリプト

    void Start ()
    {
        //ゲームマネージャの取得
        GameObject obj = GameObject.Find("gameManager");
        gameManager = obj.GetComponent<GameManager>();

        //ボールジェネレータの取得
        ballGenerator = this.GetComponent<BallGenerator>();
    }

    void Update()
    {
        float randPosX = Random.Range(-290, 290);
        transform.position = new Vector3(randPosX, transform.position.y, transform.position.z);
        //一定時間すぎたら
        if (timeCount >= generateTime)
        {
            //指定された個数ボールを生成
            if (generateCount <= generateNum)
            {
                ballGenerator.GenerateRainbowBall();
                generateCount++;
                gameManager.AddDestroyNum();
                //間隔のリセット
                timeCount = 0;
            }
            else
            {
                Destroy(gameObject);
            }
        }
        timeCount++;
    }
}
