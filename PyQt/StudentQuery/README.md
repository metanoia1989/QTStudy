# 题库学员信息查询

请求接口 POST 
```php
// 接口说明
http://www.anzhuoxfpx.com/extra_query.php
有两个参数 action mobile
action 必须为 student_info
mobile 为要查询的手机号 

// 响应值如下
{
    "code": 0,
    "msg": "",
    "data": [
        {
            "userid": "3887",
            "username": "13593871052",
            "usertruename": "刘深海",
            "regtime": "2020-05-06 16:21:14",
            "company": "广州安卓消防学院",
            "groupname": "20190614从化-初级"
        }
    ]
}
```