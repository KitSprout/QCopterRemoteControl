QCopterRC
========
[![GitHub version](https://img.shields.io/badge/QRC%20version-v1.1-brightgreen.svg)](https://github.com/KitSprout/QCopterRemoteControl/tree/QCopterRC)
[![GitHub version](https://img.shields.io/badge/QRCs%20version-v1.0-brightgreen.svg)](https://github.com/KitSprout/QCopterRemoteControl)
[![GitHub license](https://img.shields.io/badge/license-%20MIT%20%2F%20CC%20BY--SA%204.0-blue.svg)](https://github.com/KitSprout/QCopterRemoteControl/blob/master/LICENSE)
[![GitHub pcb library](https://img.shields.io/badge/pcb%20library-%20v2.16-yellow.svg)](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.16)


QCopterRemoteControl 是一個遙控器開板，四軸飛行器的控制裝置，用來與 QCopterFlightControl 溝通、控制，板上搭載搖桿與感測器，並外接顯示螢幕，可以將四軸上的回傳回來的資訊顯示出來，螢幕建立了簡單的操作介面，方便使用者設定、觀察飛控板，目前遙控器有 QCopterRC 與 QCopterRCs 兩種版本，前者使用芯片效能較高、功能多，帶高解析度的螢幕，後者功能較為簡潔，製作成本比較低。目前開發著重於 QCopterRCs，想了解 QCopterRC 的可以進入該分支 [branche](https://github.com/KitSprout/QCopterRemoteControl/tree/QCopterRC)

Hardware
========
* 控制器　 : [STM32F411CE](http://www.st.com/en/microcontrollers/stm32f411ce.html) 48Pin 100MHz DSP FPU
* 顯示器　 : [OLED_1.5-inch](https://github.com/KitSprout/OLED_1.5-inch) ( SSD1351 1.5" 128*128 )，使用 SPI 操作
* 感測器　 : [MPU9250](https://www.invensense.com/products/motion-tracking/9-axis/mpu-9250/)
* 無線傳輸 : [nRF24L01P](http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01P) + PA + LNA
* 設計軟體 [Altium Designer 17](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.16](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.16) )

View
========
<img src="https://lh3.googleusercontent.com/yntr9BMFpYGic-34lxG-xE2y1cvx4fDA4KsnnGBx9281iXgMJJvPsoLtPYLYIxTq8KDFZDCgzOw-YfHIniYJ5fK9edAF7Kb0m9LcNfn-H2dG4SHeLuK4hSUz5lgnp5Z3HbxcZUYwtdip56uL-T_LEw4nDMO3ZwoJWjuaDXx7j5EyGh7mxk65PgV-_Cok8BVIXqlq9YcyeIuz4wj4zwEymG6F8B375yncDwOTBuomEvoEXLytBWGcRDPsjHDFSVqrGuVyDRJE56DUEK0uTa2yA4grZemcJsQo0NZaunR_9Gi0O_6d8bnLVP5dn6ywELeQopd-CCDwvpy7WjKBeszFYHF39SPQMs2KwcegXq-bb4BnRE-waCbUtCb6OFEu9PuSh4JlSlZC69Au-VtufzUb5vBw_spclq_C7c_Y0FEHYT1lK7moLKIBxxK8XQuFspKSszUiqDngX_GmJOUz-8YTeGtMvX-VKUMVQyjHU2N5-BKhpAyrG_nIN1BeLQ_e4TkDYKAu6dmd6AAE2S_1Y2_tFqXM7NFSS8wWc4wHq_CRBQzB03MPTr-JOdjoAqWRJvC0NXpTzZpGJnPI13gte4fiInkYhcmB3kqPoni98xL2erpxtxGGvUTKq8ttfUUsHiM84eI53aWrK85Wbodx8ywi8-j5rJiZ7SqFhiCfpVK6Rg=w2000" />

<br />
[more photo...](https://goo.gl/photos/wA4TmWAdz5D3ZGH7A)

Config
========
<img src="https://lh3.googleusercontent.com/wru-a-LOIkKtWNAdbJupaIFEWcjBLzPYy5BGnMB46na_wLugC1QrYQlSip6l6UDza5uc2vRG8m9SGq86nt-AbfQrgNwEryrKkYSRiF3ZftJBMPneOvCXpaqvz35NMR7bK30-A1k4HxKbXCo_bfXEBBuRdM9JcTLQjWlnhf1rC3KdfaHrJzPQqIJ1MtSFachfuNQ5AS4u_r3ZccJYD6n8xOdmBZGkpekNrVd86lwMK_zoNkhAZHt2VOKp4LeqVT6OgCjS7yv2XU-G4_5KK_YArJo_fmd_trtslKzqUrQNvhVx0K0vS18PIe8HhkCqMxGVK1L9oZ1HtDMcU82IxRx3WTf3B1_SB9PepRiyrmqMECHKXFhCZ94yKccTwQouOyVkFPbgK5f3fMQQuySetL4c6yfJVMjvzeSYXXf-7PsnDGHJj1A21uJ5rH-SJAus1DXSsGT7IvlbrJIP1St8wrlJb8a2hNyedC3CDDGIxqE7qmxor7ByipkEQOXLP4sl7LJwTTKYL0DIp4UWtb6bjIJTYGWQW5JWQAD4GiGE0n5_VvqQ09--ble-C3cLMP-Pv-5A7R4fXK01BFw-u7yq6yh_SOKbe1nm5mr6qsCOgsV__xAFfmsGAtGD4Vb1RvdNghMYw0qkc_ZkfYHnUSt7Y-M1Je3Zf3J_z9MGPMMno8BrSA=w1700" />

Schematic
========
<img src="https://lh3.googleusercontent.com/h_BKrHAHg86M0zSpuiZAgYRmcqUKzyR_8aM9dXNm0h-AZk_2cAp667ZvxuubEIp2d0L1fm3B7pmYISeQfWlfnXoTIMwdMrh6geSuMyErbCDpRpujxhEZo09qlCXO2NhnDG-U7V0LZq8-PRZWUYVpcR52lDRQvaz3PNSzljxxArKLQ4eai_IDKavZRqxJq_HzJpbZIvN_GiZae7HcMhNIyDaX2zgnrSCKrlmQ16GhKFuJf8lkfHbhrtSkRyHDSLWId24VWdm-QEDsTpdwVEd2PhlRL56hgrgLhzAfn_fC70nWmCYkHcVKNOkzb0oqPDk4GjPLNxvrQ8SMD3I5N6a1LuB25Zg1R7IWe0uhUTKpIsqJR_PQIz_Usi3kGYQ8g5Lsci4RhFmsd81wjN848kDV5YJeVv55l3ry-JRIk1jVavK1YM3N9myPB3lpjXK_qtnwdzaEXW7DxnqN49QPkZpn82WBqhxP1N9S97sdse9Nt0LRwT_iBb2jVfoj62-20xuXOW4Ah2NW4np9R4ocq3oPj9vjLE5RnZHmt60tZ7mdhlW3LYJAxtB5aha0-fAQUKx7hF7bEhcwup_I0k3QvAsorIZPszI3iZ5O1x_kbtjnzdhbWw_ixGK9ss_AWeAtaOXurBbJQ_Y92R-UNUwjKH8sW88N4aVcfrOznBnpJK-PlA=w2000" />

Get it
========
Ruten Shop
