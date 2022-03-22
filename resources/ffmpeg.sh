# 将图片libyuv-rainbow-700x700.bmp转换成YUV420P格式：
ffmpeg -i rainbow.bmp -video_size 700x700 -pix_fmt yuv420p rainbow-yuv420p.yuv

# 查看YUV文件
ffplay -f rawvideo -pixel_format yuv420p -video_size 700x700 rainbow-yuv420p.yuv

ffplay -f rawvideo -pixel_format yuv420p -video_size 200x200 rainbow-yuv420p-clip-0-0.yuv

ffplay -f rawvideo -pixel_format yuv420p -video_size 100x100 rainbow-yuv420p-scale-6.yuv

ffplay -f rawvideo -pixel_format yuv420p -video_size 700x700 rainbow-yuv420p-rotation-90.yuv

ffplay -f rawvideo -pixel_format yuv420p -video_size 700x700 rainbow-yuv420p-rotation-90-mirror.yuv

ffplay -f rawvideo -pixel_format yuv420p -video_size 700x700 rainbow-yuv420p-blend.yuv