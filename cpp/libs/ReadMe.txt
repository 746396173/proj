------------------------------------------------------------------------------------------------------------------------------------------------
���ѡ��boost > std > Poco > wxWidgets��
boost�ļ���������õģ�ÿ�����¸���һ�Σ�������ΪƵ������������ѡ������std��׼�������ڲ��еģ�boost��������ˣ�����filesystem�ȣ����Ի���Ҫ��ѡ��boost��
Poco��boostһ�����ļ����������ñȽϺã�wxWidgetsһ��Ҫ��wxInitializer��ʼ�����������ж���������ʼ���ˣ�����������ѡ������
------------------------------------------------------------------------------------------------------------------------------------------------
boost Version 1.62.0

//vs2012
bjam install stage --toolset=msvc-11.0 --stagedir="F:\proj\cpp\libs\boost_lib" link=static runtime-link=static threading=multi debug release

//vs2013
bjam install stage --toolset=msvc-12.0 --stagedir="F:\proj\cpp\libs\boost_lib" link=static runtime-link=static threading=multi debug release

//����zlibĿ¼,--with-iostreams
set  ZLIB_SOURCE="F:\proj\cpp\libs\zlib-1.2.8"

//ֻ����ֻ���Ŀ�
bjam install stage --toolset=msvc-12.0 --stagedir="F:\proj\cpp\libs\boost_lib" --with-serialization link=static runtime-link=static threading=multi debug release

//���϶�û��PDB
//vs2013���԰�
bjam install stage --toolset=msvc-12.0 --build-type=complete --stagedir="F:\proj\cpp\libs\boost_lib" link=static runtime-link=static threading=multi debug release

���ȥ����boost��ȥ���е��ʼǡ�

�����Ǳ��뾲̬���ӵģ����뾲̬������Ҫ��link=shared runtime-link=shared��������������
bjam install stage --toolset=msvc-12.0 --stagedir="F:\proj\cpp\libs\boost_lib" --with-python link=shared runtime-link=shared threading=multi debug release
bjam install stage --toolset=msvc-12.0 --build-type=complete --stagedir="F:\proj\cpp\libs\boost_lib" link=shared runtime-link=shared threading=multi debug release
------------------------------------------------------------------------------------------------------------------------------------------------
