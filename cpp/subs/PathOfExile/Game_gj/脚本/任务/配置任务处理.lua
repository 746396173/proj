
�ֲ����� �������� = ���δ�������
�ֲ����� ���� = ��������
�ֲ����� ����״̬ = ��������״̬
�ֲ����� �� = ��������
�ֲ����� �� = ��������
�ֲ����� �ύ = �ύ������
�ֲ����� ��� = �ύ������
 
--Tarkleigh:������(��������)
--Nessa:��ɯ(�����ӻ�)
--Bestel:��˹��
--The Coast:ĺ�⺣̲
--Silk:˹��
--Yeena:����
--Eramir: ���׶�
--Greust:��˹��(��������)
--Yeena : ����(�����ӻ�)
�ֲ����� ���е����� = {
    [����״̬("��ʼ����")] = {
        ��(��_��ʼ����),
    },

    --���ſڵĵ���
    ����("Enemy at the Gate", {
        [����״̬("Kill Hillock")] = { --����������
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Hillock"}}}
        },
       [����״̬("Enter town for your reward")] = { --���������ȡ����
            ��(ͨ������_ɱ�������ͼ����)
        },
       [�ύ(ͨ������_�ύ����)]= {"Tarkleigh","Hillock Reward",3},
    }),

    --ҽ��֮��
    ����("Mercy Mission", {
        [����״̬("Talk to Bestel")] = {    --�Ի���˹��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Bestel"}},��}
        },
        [����״̬("Travel to The Tidal Island")] = { -- ǰ�� �����µ�  The Tidal Island(�����µ�)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","The Mud Flats"},{"��","The Tidal Island"}},"The Coast"}  --1
        },
        [����״̬("Find the Medicine Chest")] = { --�ҵ�ҽҩ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Medicine Chest"}},��}
        },
        [����״̬("Travel to Lioneye's Watch")] = { -- ǰ�� ʨ������
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Nessa for your reward")] = { --����ɯ��̸�Ի�ý���  Medicine Chest Reward(ҽҩ�佱��)
            [��(ͨ������_�ύ����)]= {"Nessa","Medicine Chest Reward",3},
        },
        [�ύ(ͨ������_�ύ����)]= {"Nessa","Medicine Chest Reward",3},
    }),
    
    --������
    ����("Breaking Some Eggs",{
        [����״̬("Travel to The Mud Flats")] = { --ǰ�� ��������
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Take the glyphs to the glyph wall")] = { --���ŵ��Ƶ�ʯ��֮��ȥ
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Strange Glyph Wall"}}} --���ŵ��Ƶ����ǽ��
        },
        [����״̬("Explore the Mud Flats")] = { --̽����������
            ��(��_̽����������)
        },
        [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Tarkleigh for your reward")] = { --����������̸����ý���  Glyph Reward(����ʯ��֮�ڵĽ���)
            [��(ͨ������_�ύ����)]= {"Tarkleigh","Glyph Reward",3},
        },
        [�ύ(ͨ������_�ύ����)]= {"Tarkleigh","Glyph Reward",3},
    }),

    --��ˮ֮Ϣ
    ��������("A Dirty Job", {
        [����״̬("Travel to The Fetid Pool")] = { --ǰ�� ��ˮ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�������","Breaking Some Eggs"}}} 
        },
        [����״̬("Kill all the monsters in the Fetid Pool")] = { --��ն�ˮ��
             ͨ��������_ȫͼɱ��
        },
        [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������
             ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Tarkleigh for your reward")] = { --����������̸����ý��� Necromancer Reward(��ն�ˮ�صĽ���)
             [��(ͨ������_�ύ����)]= {"Tarkleigh","Necromancer Reward",1},
        },
    }),

    --��ԨΣ��
    ����("The Dweller of the Deep",{
        [����״̬("Travel to The Flooded Depths")] = { --ǰ�� ˮ��֮Ԩ
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Kill the Dweller of the Deep")] = { --������Ԩ��з
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","The Deep Dweller"}}}
        },
        [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Tarkleigh for your reward")] = { --����������̸����ý��� Dweller Reward(������Ԩ��з�Ľ���)
            [��(ͨ������_�ύ����)]= {"Tarkleigh","Dweller Reward",1},
        },
    }),

    --�������
    ����("The Caged Brute",{
        [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������  Waypoint(���͵�) Lioneye's Watch(ʨ������)  The Lower Prison(����֮���²�)
             [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Waypoint"},{"ɱ����ͼ","Lioneye's Watch"}},"The Lower Prison"}
        },
        [����״̬("Talk to Nessa")] = {  --�Ի���ɳ  Prison Reward(��������)
             [��(ͨ������_�ύ����)]= {"Nessa","Prison Reward",1,"Tarkleigh"},
        },--{"ɱ������","The Warden's Chambers"},
        [����״̬("Explore the prison and Kill Brutus")] = { --̽�����������ܲ�³��˹  The Warden's Chambers(�������ķ���)  Brutus, Lord Incarcerator(��������³��˹)
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Brutus, Lord Incarcerator"}},"The Upper Prison"}
        },
        [����״̬("Travel to The Prison")] = { --ǰ�� ����֮��  The Upper Prison(����֮���ϲ�)
             [��(ͨ������_ɱ�������ͼ����)] = {{},"The Upper Prison"}
        },
        [����״̬("Kill Brutus")] = { --���ܲ�³��˹
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Warden's Chambers"},{"ɱ��","Brutus, Lord Incarcerator"}},"The Upper Prison"}
        },
        [����״̬("Find the exit from the prison")] = { --�ҳ��뿪�����ĳ���
             ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Tarkleigh for your reward")] = { --����������̸�Ի�ý���  Brutus Reward(��������Ľ���)
             [��(ͨ������_�ύ����)]= {"Tarkleigh","Brutus Reward",1}
        },
        [�ύ(ͨ������_�ύ����)]= {"Tarkleigh","Brutus Reward",1}
    }),

   --����֮��
   ����("The Siren's Cadence",{
        [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Waypoint"},{"ɱ����ͼ","Lioneye's Watch"}},"The Cavern of Wrath"}
        },
        [����״̬("Travel to Merveil's Caverns")] = { --���ܺ���.Īޱ��
            ��(��_���ܺ���)
        },
        [����״̬("Find the exit to Act Two")] = { --�ҳ�ǰ���ڶ��µ����  The Southern Forest(�ϲ�ɭ��)
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Southern Forest"}
        },
        [����״̬("Kill Merveil")] = { --����ɯ��̸  Merveil Reward(���ܺ����Ľ���)
            ��(��_���ܺ���)
        },
        [����״̬("Talk to Nessa")] = { --����ɯ��̸  Merveil Reward(���ܺ����Ľ���)
            [��(ͨ������_�ύ����)]= {"Nessa","Merveil Reward",4},
        },
    }),

    --��·�ȷ�
    ��������("The Way Forward", { 
        [����״̬("Travel to Prisoner's Gate")] = { --ǰ�� ��������  The Lower Prison(����֮���²�) Prisoner's Gate(��������)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�������","The Caged Brute"},{"ɱ����ͼ","Prisoner's Gate"}},"The Lower Prison"}  --����ȥ���������
       },
       [����״̬("Follow the Emperor's Road")] = { --�ҵ�����֮· Thaumetic Seal(����Ͽ�֮ӡ)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Thaumetic Seal"}},"Prisoner's Gate"}
       },
       [����״̬("Find another way to the forest")] = { --�ҵ�����ͨ��ɭ�ֵ�· --ת������֮��  The Cavern of Wrath(Թ��֮��)  The Cavern of Anger(Թ��֮���)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�������","The Siren's Cadence"},{"ɱ����ͼ","The Cavern of Anger"},{"ɱ��","ħ��֮��Īޱ��"}},"The Cavern of Wrath"}
       },
       [����״̬("Find the forest encampment")] = { --�ҵ�ɭ��Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
       },
       [����״̬("Talk to Silk")] = { --��˹�˽�̸
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Silk"}}}
       },
       [����״̬("Travel to The Western Forest")] = { --ǰ�� ��������
            ��(ͨ������_ɱ�������ͼ����)
       },
       [����״̬("Open the blocked pass")] = { --��ͨ����ϵĵ�·
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Thaumetic Seal"}}}
       },
       [����״̬("Kill the Blackguards")] = { --������������  Thaumetic Emblem(��������)
             [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Thaumetic Emblem"}}}
       },
       [����״̬("Activate the Thaumetic Seal")] = { --��������Ͽ˷�ӡ
             [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Thaumetic Seal"}}}
       },
       [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������
             ��(ͨ������_ɱ�������ͼ����)
       },
       [����״̬("Talk to Bestel for your reward")] = { --���˹�ؽ�̸����ý��� Reopened Passage(��·����)
            [��(ͨ������_�ύ����)]= {"Bestel","Reopened Passage",1},
        },
   }),

   --��ɫ����
   ����("The Great White Beast",{
        [����״̬("Travel to The Den")] = { --ǰ�� ��Ѩ
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the Great White Beast")] = { --���԰�ɫ���� The Great White Beast(��ɫ����)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","The Great White Beast"}}}
        },
        [����״̬("Kill the Great White Beast")] = { --���ܰ�ɫ����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","The Great White Beast"}}}
        },
        [����״̬("Travel to The Forest Encampment")] = { --ǰ�� ɭ��Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Yeena for your reward")] = { --�����Ƚ�̸����ý���
            [��(ͨ������_�ύ����)]= {"Yeena","Great White Beast Reward",3},
        },          --Great White Beast Reward(���ܰ�ɫ���޵Ľ���)
        [�ύ(ͨ������_�ύ����)]= {"Yeena","Great White Beast Reward",3},
   }),

   --������Ǵ򽻵�
   ����("Deal with the Bandits",{
        [����״̬("Travel to The Broken Bridge, The Western Forest or The Wetlands")] = {  --ǰ�� ���϶���, �������� ���� ʪ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Eramir wants you to kill Kraityn")] = { --���׶�Ҫ��ɵ����׶� --Kraityn's Amulet(�����ǵĹ���֮��)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"����","Kraityn"},{"��","Kraityn's Amulet"}},��},
        },
        [����״̬("Travel to The Western Forest or The Wetlands")] = { --ǰ�� �������� ���� ʪ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Eramir wants you to kill Alira")] = {  --���׶�Ҫ��ɵ���������ŷ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"����","Alira"},{"��","Alira's Amulet"}},��},
        },
        [����״̬("Travel to The Wetlands")] = { --ǰ�� ʪ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Eramir wants you to kill Oak")] = { --���׶�Ҫ��ɵ�ŷ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"����","Oak"},{"��","Oak's Amulet"}},��},
        },
        [����״̬("Travel to The Forest Encampment")] = { --ǰ�� ɭ��Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Eramir for your reward")] = { --�밬�׶���̸����ý���
            [��(ͨ������_�ύ����)]= {"Eramir","Take the Apex",1},
            --[��(ͨ������_��ȡ����)] = {"Eramir",{{"Take the Apex",1}}}
        },
   }),

   --�߶�֮Ӱ
   ����("Shadow of the Vaal",{	
        [����״̬("Talk to Eramir")] = { --�밬�׶���̸
           [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Eramir"}}}
        },
        [����״̬("Find the Ancient Pyramid")] = {--�ҵ��Ž�����
            [��(ͨ������_ɱ�������ͼ����)] = {{},"The Ancient Pyramid"}
        },
        [����״̬("Ascend the Ancient Pyramid")] = {--����-ɱ������ ���������� �� �ڰ���̳
           [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Pyramid Apex"},{"��","Dark Altar"}},"The Ancient Pyramid"}
        },
        [����״̬("Travel to The Caverns")] = {--ǰ�� �ٲ���Ѩ
            [��(ͨ������_ɱ�������ͼ����)] = {{},"The Ancient Pyramid"}
        },
        [����״̬("Activate the Dark Altar")] = {--�����ڰ���̳
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Pyramid Apex"},{"��","Dark Altar"}},"The Ancient Pyramid"}
        },
        [����״̬("Kill the Vaal Oversoul")] = {--�����߶�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Vaal Oversoul"}},"The Ancient Pyramid"}
        },
        [����״̬("Find the exit to Act Three")] = {--�ҵ�ǰ�������µĳ���--�����Ƿ���
            [��(ͨ������_ɱ�������ͼ����)] = {{},"The City of Sarn"}
        },
        [����״̬("Find the Sarn encampment")] = {--�ҵ�����Ӫ��  --��������  --�ҵ�����Ӫ��   --�����Ƿ���
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Clarissa"},{"��","The Sarn Encampment"}},"The City of Sarn"}
        },
   }),

   --��ɫ������
   ����("Intruders in Black",{
        [����״̬("Travel to The Chamber of Sins")] = { --ǰ�� ����֮��
            ��(ͨ������_ɱ�������ͼ����)
        },  
        [����״̬("Explore the Chamber of Sins")] = { --��������֮��.   Fidelitas, the Mourning(�����߷ѵ�����˹)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Fidelitas, the Mourning"}}}
        },
        [����״̬("Kill Fidelitas")] = { --���ܷѵ�˹��˹
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Fidelitas, the Mourning"}}}
        },
        [����״̬("Get the Baleful Gem")] = { --ȡ��аӰ��ʯ   Baleful Gem(аӰ��ʯ) Strange Device(��ֵ�װ��)

            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Strange Device"},{"��","Baleful Gem"}}}
        },
        [����״̬("Travel to The Forest Encampment")] = { --ǰ�� ɭ��Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Helena")] = { --������Ƚ�̸
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Helena"}}}
        },      --Blackguard Reward(ȡ��аӰ��ʯ�Ľ���)
        [�ύ(ͨ������_�ύ����)]= {"Greust","Blackguard Reward",3},
   }),

   --����֩��
   ����("Sharp and Cruel",{
        [����״̬("Talk to Silk")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Silk"}}}
        },
        [����״̬("Travel to The Weaver's Chambers")] = { --ǰ�� ֯���߳�Ѩ
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find Maligaro's Spike")] = { --�ҳ������׸��޵ļ�̡�
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Weaver's Nest"},{"��","Maligaro's Spike"}}}
        },
        [����״̬("Get Maligaro's Spike")] = { --ȡ�á����׸��޵ļ�̡�
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Weaver's Nest"},{"��","Maligaro's Spike"}}}
        },
        [����״̬("Travel to The Forest Encampment")] = { --ǰ�� ɭ��Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Silk for your reward")] = { --��˹�˽�̸����ý��� Maligaro's Spike Reward(���׸��޵ļ�̽���)
            [��(ͨ������_�ύ����)]= {"Silk","Maligaro's Spike Reward",1},
        },
   }),

   --����ʥ��
   ����("Through Sacred Ground",{
        [����״̬("Travel to The Crypt")] = { --ǰ�� �ž���Ĺ
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the Golden Hand")] = { --�ҵ��ƽ�֮��  {"ɱ��","Altar"},   Altar(��̳) Golden Hand(�ƽ�֮��),The Crypt Level 2(�ž���Ĺ 2 ¥)
            [��(ͨ������_ɱ�������ͼ����)] ={{{"��","Golden Hand"}},"The Crypt Level 2"}
        },
        [����״̬("Travel to The Forest Encampment")] = {  --ǰ�� ɭ��Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Yeena for your reward")] = { --�����Ƚ�̸����ý���  Jewel Reward(�鱦����) Fellshrine Reward(�ƽ�֮�ֵĽ���)
           [��(ͨ������_��ȡ����)] = {"Yeena",{{"Jewel Reward",1},{"Fellshrine Reward",1}}}
        },
   }),

   --�̸����
   ����("The Root of the Problem",{
        [����״̬("Travel to The Wetlands")] = { --ǰ�� ʪ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Poison the ancient tree")] = { --���������� Tree Roots(����)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Tree Roots"}}}
        },
        [����״̬("Travel to The Vaal Ruins")] = { --ǰ�� �߶�����
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find a way through the Vaal Ruins")] = {  --�ҵ������߶��ż��ķ��� The Northern Forest(��������)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Waypoint"}},"The Northern Forest"}
        },
   }),

   --��ʧ�İ���
   ����("Lost in Love",{ 
        [����״̬("Find the Sarn encampment")] = { --ǰ�� �����Ƿ���
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Clarissa"},{"��","The Sarn Encampment"}},"The City of Sarn"}
        },
        [����״̬("Travel to The City of Sarn")] = { --ǰ�� �����Ƿ���
             ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Defeat the guards and rescue the girl")] = {--��������������Ů��
            ��(��_�������������Ů��)
        },
        [����״̬("Find Clarissa and Tolman")] = {-- ע�����״̬��
            ��(��_�������������Ů��)
        },
        [����״̬("Find Tolman in the Crematorium")] = {--�ڻ��᳡�ҵ��ж���--�ɵ�--�ж���
            --[��(ͨ������_ɱ�������ͼ����)] = { { {"ɱ��","Tolman"},{"��","Tolman"},{"ʰȡ","������Ʒ"} },��},
            [��(ͨ������_ɱ�������ͼ����)] = { { {"ɱ��","Tolman"},{"��","Tolman's Bracelet"} },��},
        },  
        [����״̬("Get Tolman's bracelet")] = { --ȡ���ж���������
            --[��(ͨ������_ɱ�������ͼ����)] = { { {"ɱ��","Piety"},{"��","Tolman"},{"ʰȡ","������Ʒ"} },��},
            [��(ͨ������_ɱ�������ͼ����)] = { { {"��","Tolman's Bracelet"} },��},
        },
        [����״̬("Travel to The Sarn Encampment")] = { --ǰ�� ����Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Clarissa")] = {--�뿨��������̸--ȡ����ˮ��Կ��
            [��(ͨ������_�ύ����)] = {"Clarissa","Take Sewer Keys",1},
        },
		--���һ���µ����ֹ���߶ϵ���
		[����״̬("Talk to Maramoa,Talk to Clarissa")] = {--������Ī��̸����ý���   --��������ȥ�ӱ�ʯ�ʺ�����
           [��(ͨ������_�ύ����)] = {"Clarissa","Take Sewer Keys",1},
        },
        [����״̬("Talk to Maramoa for your reward")] = {--������Ī��̸����ý���   --��������ȥ�ӱ�ʯ�ʺ�����
            [��(ͨ������_�ύ����)] = {"Maramoa","Clarissa Reward",4,"Grigor"},
        },
   }),

   --��ʯ�ʺ�
   ����("The Gemling Queen",{
        [����״̬("Travel to The Solaris Temple")] = {--ǰ�� ��ҫ���
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the tomb of the Gemling Queen")] = { --�ҳ���ʯ�ʺ����Ĺ  --��������
             [��(ͨ������_ɱ�������ͼ����) ] = {{{"ɱ��","Lady Dialla"},{"�Ի�","Lady Dialla"}},��}
        },
   }),

   --˿������
   ����("The Ribbon Spool",{
        [����״̬("Travel to The Battlefront")] = { --ǰ�� ��ս�㳡
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the Ribbon Spool")] = {--�ҳ�˿������ --�д�֮��
            [��(ͨ������_ɱ�������ͼ����) ] = {{{"��","Ribbon Spool"}},��}
        },
        [����״̬("Travel to The Solaris Temple")] = {--ǰ�� ��ҫ���
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Lady Dialla for your reward")] = {--��������˽�̸����ý���--ȡ�ضд�֮��Ľ���
            [��(ͨ������_�ύ����)]= {"Lady Dialla","Ribbon Spool Reward",1},
        },
   }),

   --���֮��
   ����("Fiery Dust",{
        [����״̬("Travel to The Docks")] = {--ǰ�� ���ຣ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the Thaumetic Sulphite")] = {--�ҳ�����Ͽ�������--����Ͽ�������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Supply Container"},{"��","Thaumetic Sulphite"}},��}
        },
        [����״̬("Travel to The Solaris Temple")] = {--ǰ�� ��ҫ���
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Lady Dialla")] = {--��������˽�̸--ȡ������֮��
            [��(ͨ������_�ύ����)]= {"Lady Dialla","Take Infernal Talc",1},
        },
        [����״̬("Travel to The Warehouse Sewers")] = {--ǰ�� �ֿ�ش���ˮ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Destroy the Undying Blockage")] = {--�ݻٲ�������--��������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Undying Blockage"}},��}
        },
   }),

   --ά�����µ��ر�
   ����("Victario's Secrets",{ 
        [����״̬("Talk to Hargan")] = {--��ظ���̸
             [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Hargan"}},��}
        },
        [����״̬("Find the platinum bust")] = { --�ҳ������� --���ﴦ(Stash) ���������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Stash"},{"ʰȡ","������Ʒ"}},"��ǰ��ͼ"}
        },
        [����״̬("Travel to The Sarn Encampment")] = { --ǰ�� ����Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Market Sewers")] = { --ǰ�� �м��ش���ˮ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Market Sewers"}
        },
        [����״̬("Travel to The Warehouse Sewers")] = { --ǰ�� �ֿ�ش�
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Warehouse Sewers"}
        },
        [����״̬("Travel to The Slums Sewers or The Warehouse Sewers")] = { --ǰ�� ǰ�� ƶ�����ˮ�� ���� �м��ش���ˮ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Slums Sewers"}
        },
        [����״̬("Travel to The Slums Sewers or The Market Sewers")] = { --ǰ�� ǰ�� ƶ�����ˮ�� ���� �м��ش���ˮ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Slums Sewers"}
        },
        [����״̬("Talk to Hargan for your reward")] = {--��ظ���̸����ý���--ά����µĽ���
            [��(ͨ������_�ύ����)]= {"Hargan","Victario Reward",1},
        },
   }),

   --����������
   ����("Sever the Right Hand",{ 
        [����״̬("Travel to The Ebony Barracks")] = {--ǰ�� ����������Ӫ
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Kill General Gravicius")] = { --���ܸ���ά�潫��--����ά�潫��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","General Gravicius"}}}
        },  
        [����״̬("Travel to The Sarn Encampment")] = {--ǰ�� ����Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Maramoa for your reward")] = {--������Ī��̸����ý���--���ܽ����Ľ���
            [��(ͨ������_�ύ����)]= {"Maramoa","Gravicius Reward",4},
        },
   }),

   --�ɵٵĳ���
   ����("Piety's Pets",{
        [����״̬("Travel to The Lunaris Temple")] = {--ǰ�� ��Ӱ���
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find Piety")] = {--�ҳ��ɵ�--������--����֮Կ--��Ӱ���:�� 2 ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Tower Key"}},"The Lunaris Temple Level 2"},
        },
        [����״̬("Kill Piety")] = {--�����ɵ�q {"ɱ������","Portal"}
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Tower Key"}},"The Lunaris Temple Level 2"},
        },
        [����״̬("Travel to The Sarn Encampment")] = {--ǰ�� ����Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Grigor for your reward")] = {--�����꽻̸����ý���--�����ɵٵĽ���
            [��(ͨ������_�ύ����)]= {"Grigor","Piety Reward",1},
        },
   }),

   --��Ȩ֮��
   ����("Sceptre of God",{
        [����״̬("Travel to The Imperial Gardens")] = {--ǰ�� �ʼһ�԰(�ӵ�ͼ:�����Թ�)
            ��(ͨ������_ɱ�������ͼ����)
        },
--        [����״̬("Unlock the Sceptre of God")] = {--ǰ�� ��Ȩ֮��
--            ��(ͨ������_ɱ�������ͼ����)
--        },
        [����״̬("Travel to The Lunaris Temple")] = {--ǰ�� ��Ӱ���
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find Piety")] = {--ȡ���ɵٵ�Կ��--����֮Կ
        [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Portal"},{"��","Tower Key"}},"The Lunaris Temple Level 2"},
        },
        [����״̬("Unlock the Sceptre of God")] = {--����Ȩ֮���Ĵ���--��������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Locked Door"}},��}
        },
        [����״̬("Travel to The Sceptre of God")] = {--ǰ����Ȩ֮���Ķ���--"�ϲ���Ȩ֮��--����֮������
            --[��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Dominus"}},"The Upper Sceptre of God"}
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","Boos Pos"}},"The Upper Sceptre of God"}
        },
	    [����״̬("Ascend the Sceptre of God")] = {--������Ȩ֮���Ķ��� {"ɱ������","Portal"}, {"ɱ��","Dominus, High Templar"}
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","Boos Pos"},{"ɱ��","Dominus, Ascendant"}},"The Upper Sceptre of God"}
        },
        [����״̬("Fight your way to Dominus")] = {--��������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","Boos Pos"},{"ɱ��","Dominus, Ascendant"}},"The Upper Sceptre of God"}
        },
		[����״̬("Kill Dominus")] = {--��������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","Boos Pos"},{"ɱ��","Dominus, Ascendant"}},"The Upper Sceptre of God"}
        },
        [����״̬("Talk to Dialla")] = {--��������˽�̸
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Lady Dialla"}},"The Upper Sceptre of God"}
        },
        [����״̬("Find the exit to Act Four")] = {--�ҵ�ǰ�������µĳ���--ˮ���ż�
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Aqueduct"}},"The Upper Sceptre of God"}
        },
   }),

      --�����Ŀ���
   ����("A Swig of Hope",{
        [����״̬("Return to The Ship Graveyard in Act One")] = {  --The Ship Graveyard(��Ӱ��Ĺ)
            [��(ͨ������_ɱ�������ͼ����)] = {{},"The Ship Graveyard"}
        },
        [����״̬("Travel to The Docks")] = { --ǰ�� ���ຣ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Search the Docks")] = { --�������ຣ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Captain Fairgraves"},{"�Ի�","Captain Fairgraves"}}}
        },
        [����״̬("Travel to The Imperial Gardens")] = { --ǰ�� �ʼһ�԰(�ӵ�ͼ:�����Թ�)
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find Chitus' Plum")] = { --�ҳ�������˹��÷������  Chitus' Plum������˹��÷���� The Hedge Maze(�����Թ�)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Plum"},{"��","Chitus' Plum"}},"The Hedge Maze"}
        },
        [����״̬("Talk to Fairgraves")] = { --��Ѷ�������̸ Swig of Hope Reward(ȡ�þۻ����ƵĽ���)
            [��(ͨ������_�ύ����)] = {"Captain Fairgraves","Swig of Hope Reward",1}
        }
   }),

   --�������ˮ��
   ����("The Marooned Mariner",{
        [����״̬("Find Fairgraves")] = { --�ҵ��Ѷ�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Captain Fairgraves"},{"�Ի�","Captain Fairgraves"}}}
        },
        [����״̬("Find the Allflame")] = { --�ҵ�����֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Allflame"}}}
        },
        [����״̬("Travel to The Ship Graveyard Cave")] = { --ǰ�� ��Ӱ��Ĺ
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Ship Graveyard")] = { --ǰ�� ��Ӱ��Ĺ
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Bring the Allflame to Fairgraves")] = { --������֮�𽻸��Ѷ�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Captain Fairgraves"},{"�Ի�","Captain Fairgraves"}}}
        },
        [����״̬("Kill Fairgraves")] = { --�ҵ�����֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Captain Fairgraves"}}}
        },
        [����״̬("Travel to Lioneye's Watch")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Bestel for your reward")] = { --���˹�ؽ�̸����ý��� Fairgraves Reward(���ܷѶ������Ľ���)
            [��(ͨ������_�ύ����)]= {"Bestel","Fairgraves Reward",1},
        },
        [�ύ(ͨ������_�ύ����)]= {"Bestel","Fairgraves Reward",1},
   }),

   --ͻ�Ʒ�ӡ
   ����("Breaking the Seal",{
        [����״̬("Find Deshret's Banner in the Dried Lake")] = {--�ҵ��������ص�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Deshret's Banner"}}}
        },
        [����״̬("ǰ�� �ɺԺ���")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Take Deshret's Banner")] = {--ȡ�ص������ص�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Deshret's Banner"}}}
        },
        [����״̬("Travel to Highgate")] = {--ǰ�� ͳ����֮��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Oyun")] = {--�Ի� ŷ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Oyun"}}}
        },
        [����״̬("Use Deshret's Banner on the Seal to open the Mines")] = {--ʹ�������Ƴ��������صķ�ӡ
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Deshret's Seal"}}}
        },
        [����״̬("Kill Voll and take Deshret's Banner")] = { --���ܸ�����ȡ�ص������ص�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Deshret's Banner"}}}
        },
        [����״̬("Talk to Oyun for your reward")] = {--�Ի�Oyun--���콱��
            [��(ͨ������_�ύ����)]= {"Oyun","Red Banner Reward",4},
        },
    }),

    --������־ 
    ����("An Indomitable Spirit",{ 
        [����״̬("Find Deshret's spirit")] = { --�ͷŵ������ص����  The Mines Level 2(��ڿ��:�� 2 ��)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Deshret's Spiriteee"}},"The Mines Level 2"}
        },
--        [����״̬("ǰ�� ��ڿ��")] = {
--            [��(ͨ������_ɱ�������ͼ����)] = {{},"��ڿ��:�� 2 ��"}
--        },  
        [����״̬("Talk to Tasuni in town for your reward")] = { --��Ӫ�صĴ����ύ̸�Ի�ȡ���� --Deshret Reward(�������ؽ���)
            [��(ͨ������_�ύ����)]= {"Tasuni","Deshret Reward",1},
        },

   }),

   --��ŭ֮��
   ����("The King of Fury",{
        [����״̬("Find Kaom and the Eye of Fury")] = {--�ҵ���ķ���ŭ֮��-- --��ŭ֮�� {"ɱ������","Caldera of The King"},
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Eye of Fury"}},"Kaom's Stronghold"}
        },
        [����״̬("Kill Kaom")] = {--���ܸ�ķ--��ķ�ı���--Caldera of The King����֮�� {"ɱ������","Caldera of The King"},
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Eye of Fury"}},"Kaom's Stronghold"}
        },
        [����״̬("Travel to The Crystal Veins")] = {--ǰ�� ˮ������  --ͳ����֮��
            [��(ͨ������_ɱ�������ͼ����)] =  {{{"ɱ����ͼ","The Crystal Veins"}},"Highgate"}
        },
        [����״̬("Travel to Kaom's Stronghold")] = {--ǰ�� ��ķ�ı���
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Kaom's Dream"},{"�Ի�","Lady Dialla"}}}
        },
        [����״̬("Deliver the Eye of Fury to Dialla")] = {--�ѷ�ŭ֮�۽�������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Kaom's Dream"},{"�Ի�","Lady Dialla"}}}
        },
        [����״̬("Talk to Dialla in town for a reward")] = {--��Ӫ�صĴ�����̸�Ի�ȡ����
            [��(ͨ������_�ύ����)]= {"Dialla","Rapture Reward",1},
        },
   }),

   --����֮��
   ����("The King of Desire",{
        [����״̬("Find Daresso and the Eye of Desire")] = {-- �ҵ�������������֮��--����֮��--����֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Ring Blades"},{"��","The Eye of Desire"}}}
        },
        [����״̬("Kill Daresso")] = {--���ܵ�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Ring Blades"},{"��","The Eye of Desire"}}}
        },
        [����״̬("Take the Eye of Desire")] = {--ȡ������֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Eye of Desire"}}}
        },
        [����״̬("Travel to The Crystal Veins")] = {--ǰ�� ˮ������--ͳ����֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Crystal Veins"}},"Highgate"}
        },
        [����״̬("Deliver the Eye of Desire to Dialla")] = {--������֮�۽�������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"����","Lady Dialla"},{"�Ի�","Lady Dialla"}}}
        },
   }),

   --��������
   ����("The Eternal Nightmare",{
        [����״̬("Travel to Highgate")] = {--ǰ�� ͳ����֮��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Dialla")] = {--�������̸
            [��(ͨ������_ɱ�������ͼ����)] = { {{"�Ի�","Lady Dialla"}},��}
        },
        [����״̬("Talk to Oyun")] = {--��ŷ�Ŷ���̸
            [��(ͨ������_ɱ�������ͼ����)] = { {{"�Ի�","Oyun"}},��}
        },
        [����״̬("Find the Rapture Device")] = {--�ҵ��ѽ�װ��--��ķ�Ļþ�
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Kaom's Dream"},{"�Ի�","Lady Dialla"}}}
        },
        [����״̬("Travel to The Belly of the Beast")] = {--����֮��:�� 1 ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Belly of the Beast Level 1"}},"The Crystal Veins"}  
        },
        [����״̬("Destroy the Beast within")] = {--�������֮��--�޸�The Bowels of the Beast--�ɵ�,��������--����֮��:�� 2 ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Bowels of the Beast"},{"ɱ��","Piety, the Abomination"}},"The Belly of the Beast Level 2"}
        },
        [����״̬("Kill Piety")] = {  --��С��ͼ����  ������������´�ע���� --����֮��:�� 2 ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Piety, the Abomination"}},"The Belly of the Beast Level 2"}
        },
        [����״̬("Talk to Piety")] = {--���ɵٽ�̸  --��С��ͼ����  ������������´�ע����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Piety"}},"The Belly of the Beast Level 2"}
        },
        [����״̬("Travel to The Harvest")] = {       --ǰ�� ����֮��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find a way into the Black Core")] = { --�ҵ����������ĵ�·  --�����Ҫ�Զ��� һЩ������
            ��(��_�ҵ����������ĵ�·)
        },
        [����״̬("Enter the Black Core")] = {--����������--Malachai, The Nightmare����������
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Black Core"},{"ɱ��","Malachai, The Nightmare"}}}
        },
        [����״̬("Kill Malachai")] = {  --�����������������Խ���������     -- �����Ҫɱ�����ֲ��� ����״̬������ı�
            ��(��_�ҵ����������ĵ�·)
            --[��(ͨ������_ɱ�������ͼ����)] = {{{"��","�������"}}}
        },
        [����״̬("Kill The Nightmare")] = { --����û������ȶ�   --ɱ���� �򿪺������
            ��(��_����������)
        },
    }),



   ---------------һ�� �Ѷ�  �������-------------------
   ----��������һ�� ������  ������̲(�п�)
}

���������()
����������(���е�����)

