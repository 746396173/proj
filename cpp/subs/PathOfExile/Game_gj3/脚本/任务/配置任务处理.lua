
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

    ����("The Lord's Labyrinth",{
        [����״̬("Enter the Labyrinth")] = { 
             [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Trial of Ascendancy Plaque"}},"��ǰ��ͼ"}
        },
        [����״̬("Solve the Trials of Ascendancy")] = {    --The Crypt
             ��(��_ǰ������)
        },
        [����״̬("Solve the Trial of Ascendancy in this Area")] = { 
             ��(��_��ͼ����)
        },
        [����״̬("Complete the Labyrinth")] = { 
             ��(��_����Թ�)
        },
        [����״̬("Travel to The Sarn Encampment")] = { 
             [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Sarn Encampment"}
        },
        [����״̬("Enter the Labyrinth in the Sarn Encampment")] = { 
             [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Ascendancy Plaque"}},"The Sarn Encampment"}
        },
        [����״̬("Activate the Altar of Ascendancy")] = { 
              ��(��_����Թ�)
        },
    }),

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
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Mud Flats"}
        },
        [����״̬("Take the Glyphs to the Glyph Wall")] = { --���ŵ��Ƶ�ʯ��֮��ȥ
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
    ��������("The Caged Brute",{
        [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������  Waypoint(���͵�) Lioneye's Watch(ʨ������)  The Lower Prison(����֮���²�)
             [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Waypoint"},{"ɱ����ͼ","Lioneye's Watch"}},"The Lower Prison"}
        },
        [����״̬("Talk to Nessa")] = {  --�Ի���ɳ  Prison Reward(��������)
             [��(ͨ������_�ύ����)]= {"Nessa","Prison Reward",1,"Tarkleigh"},
        },--{"ɱ������","The Warden's Chambers"},
        [����״̬("Explore the Prison and kill Brutus")] = { --̽�����������ܲ�³��˹  The Warden's Chambers(�������ķ���)  Brutus, Lord Incarcerator(��������³��˹)
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Warden's Chambers"},{"ɱ��","Brutus, Lord Incarcerator"}},"The Upper Prison"}
        },
        [����״̬("Travel to The Prison")] = { --ǰ�� ����֮��  The Upper Prison(����֮���ϲ�)
             ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Kill Brutus")] = { --���ܲ�³��˹
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Warden's Chambers"},{"ɱ����ͼ","Prisoner's Gate"}},"The Upper Prison"}
        },
        [����״̬("Find the exit from the Prison")] = { --�ҳ��뿪�����ĳ���
             ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Tarkleigh for your reward")] = { --����������̸�Ի�ý���  Brutus Reward(��������Ľ���)
             [��(ͨ������_�ύ����)]= {"Tarkleigh","Prison Reward",1}
        },
        [�ύ(ͨ������_�ύ����)]= {"Tarkleigh","Prison Reward",1} 
    }),



   --����֮��
   ����("The Siren's Cadence",{
        [����״̬("Travel to Lioneye's Watch")] = { --ǰ�� ʨ������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Waypoint"},{"ɱ����ͼ","Lioneye's Watch"}},"The Cavern of Wrath"}
        },
        [����״̬("Travel to Merveil's Caverns")] = { --���ܺ���.Īޱ��
            ��(��_���ܺ���)
        },
        [����״̬("Find the exit to Act 2")] = { --�ҳ�ǰ���ڶ��µ����  The Southern Forest(�ϲ�ɭ��)
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
       [����״̬("Find the Forest Encampment")] = { --�ҵ�ɭ��Ӫ��
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
        [����״̬("Find the exit to Act 3")] = {--�ҵ�ǰ�������µĳ���--�����Ƿ���
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
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Fidelitas, the Mourning"}},"The Chamber of Sins Level 2"}
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
        [����״̬("Talk to Helena")] = { --������Ƚ�̸ --���������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Helena"}},"��ǰ��ͼ"}
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
        [����״̬("Find Maligaro's Spike")] = { --�ҳ������׸��޵ļ�̡�{"ɱ������","The Weaver's Nest"},
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","Maligaro's Spike"},{"��","Maligaro's Spike"}}}
        },
        [����״̬("Get Maligaro's Spike")] = { --ȡ�á����׸��޵ļ�̡�
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","Maligaro's Spike"},{"��","Maligaro's Spike"}}}
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
        [����״̬("Kill Clarissa's guards")] = {-- ע�����״̬��
            ��(��_�������������Ů��)
        },
        [����״̬("Find Tolman in the Crematorium")] = {--�ڻ��᳡�ҵ��ж���--�ɵ�--�ж���
            --[��(ͨ������_ɱ�������ͼ����)] = { { {"ɱ��","Tolman"},{"��","Tolman"},{"ʰȡ","������Ʒ"} },��},
            [��(ͨ������_ɱ�������ͼ����)] = { { {"ɱ��","Tolman"},{"��","Tolman's Bracelet"} },��},
        },
        [����״̬("Find Clarissa and Tolman")] = {--�ڻ��᳡�ҵ��ж���--�ɵ�--�ж���
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
        [����״̬("Travel to The Solaris Temple Level 2")] = {--ǰ�� ��ҫ���
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
        [����״̬("Travel to The Solaris Temple Level 2")] = {--��������˽�̸����ý���--ȡ�ضд�֮��Ľ���
            ��(ͨ������_ɱ�������ͼ����)
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
        [����״̬("Travel to The Solaris Temple Level 2")] = {--ǰ�� ��ҫ���
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Lady Dialla")] = {--��������˽�̸--ȡ������֮��
            [��(ͨ������_�ύ����)]= {"Lady Dialla","Take Infernal Talc",1},
        },
        [����״̬("Travel to The Warehouse Sewers")] = {--ǰ�� �ֿ�ش���ˮ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Sewers")] = {--ǰ�� �ֿ�ش���ˮ��
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
        [����״̬("Find the platinum bust")] = { --�ҳ������� --���ﴦ(Stash)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Stash"},{"ʰȡ","������Ʒ"}},"��ǰ��ͼ"}
        },
        [����״̬("Find the third Platinum Bust")] = { --�ҳ������� --���ﴦ(Stash)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Stash"},{"ʰȡ","������Ʒ"}},"��ǰ��ͼ"}
        },
        [����״̬("Find the two remaining Platinum Busts")] = { --�ҳ������� --���ﴦ(Stash)
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Stash"},{"ʰȡ","������Ʒ"}},"��ǰ��ͼ"}
        },
        [����״̬("Travel to The Sarn Encampment")] = { --ǰ�� ����Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Sewers")] = { 
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
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Portal"},{"��","Tower Key"}},"The Lunaris Temple Level 2"},
        },
        [����״̬("Kill Piety")] = {--�����ɵ�q
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Portal"},{"��","Tower Key"}},"The Lunaris Temple Level 2"},
        },
        [����״̬("Travel to The Sarn Encampment")] = {--ǰ�� ����Ӫ��
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Grigor for your reward")] = {--�����꽻̸����ý���--�����ɵٵĽ���
            [��(ͨ������_�ύ����)]= {"Grigor","Piety Reward",1},
        },
   }),

   --��Ȩ֮�� 
   ����("The Sceptre of God",{
        [����״̬("Travel to The Imperial Gardens")] = {--ǰ�� �ʼһ�԰(�ӵ�ͼ:�����Թ�)
            ��(ͨ������_ɱ�������ͼ����)
        },
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
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Dominus"}},"The Upper Sceptre of God"}
        },
		[����״̬("Ascend the Sceptre of God")] = {--������Ȩ֮���Ķ��� {"ɱ������","Portal"},
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","BOOS"},{"ɱ��","Dominus Ascendant"}},"The Upper Sceptre of God"}
        },
        [����״̬("Fight your way to Dominus")] = {--��������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Tower Rooftop"},{"ɱ��","Dominus Ascendant"}},"The Upper Sceptre of God"}
        },
		[����״̬("Kill Dominus")] = {--��������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Tower Rooftop"},{"ɱ��","Dominus Ascendant"}},"The Upper Sceptre of God"}
        },
        [����״̬("Talk to Dialla")] = {--��������˽�̸
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Lady Dialla"}},"The Upper Sceptre of God"}
        },
        [����״̬("Find the exit to Act 4")] = {--�ҵ�ǰ�������µĳ���--ˮ���ż�
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
        [����״̬("Find Kaom and the Eye of Fury")] = {--�ҵ���ķ���ŭ֮��-- --��ŭ֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Caldera of The King"},{"��","The Eye of Fury"}},"Kaom's Stronghold"}
        },
        [����״̬("Kill Kaom")] = {--���ܸ�ķ--��ķ�ı���--Caldera of The King����֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Caldera of The King"},{"��","The Eye of Fury"}},"Kaom's Stronghold"}
        },
        [����״̬("Travel to The Crystal Veins")] = {--ǰ�� ˮ������  --ͳ����֮��
            [��(ͨ������_ɱ�������ͼ����)] =  {{{"ɱ����ͼ","The Crystal Veins"}},"Highgate"}
        },
        [����״̬("Travel to Kaom's Stronghold")] = {--ǰ�� ��ķ�ı���
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Lady Dialla"}}}
        },
        [����״̬("Deliver the Eye of Fury to Dialla")] = {--�ѷ�ŭ֮�۽�������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Kaom's Dream"},{"�Ի�","Lady Dialla"}}}
        },
        [����״̬("Take the Eye of Fury")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Eye of Fury"}},"Kaom's Stronghold"}
        },
        [����״̬("Talk to Dialla in town for a reward")] = {--��Ӫ�صĴ�����̸�Ի�ȡ����
            [��(ͨ������_�ύ����)]= {"Dialla","Rapture Reward",1},
        },
   }),

   --����֮��
   ����("The King of Desire",{
        [����״̬("Find Daresso and the Eye of Desire")] = {-- �ҵ�������������֮��--����֮��--����֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Ring of Blades"},{"��","The Eye of Desire"}}}
        },
        [����״̬("Kill Daresso")] = {--���ܵ�����
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Ring of Blades"},{"��","The Eye of Desire"}}}
        },
        [����״̬("Take the Eye of Desire")] = {--ȡ������֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Eye of Desire"}}}
        },
        [����״̬("Travel to The Crystal Veins")] = {--ǰ�� ˮ������--ͳ����֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Crystal Veins"}},"Highgate"}
        },
        [����״̬("Deliver the Eye of Desire to Dialla")] = {--������֮�۽�������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Kaom's Dream"},{"����","Lady Dialla"},{"�Ի�","Lady Dialla"}}}
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
        [����״̬("Talk to Tasuni")] = {
            [��(ͨ������_ɱ�������ͼ����)] = { {{"�Ի�","Tasuni"}},��}
        },
        [����״̬("Find the Rapture Device")] = {--�ҵ��ѽ�װ��--��ķ�Ļþ�
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Kaom's Dream"},{"�Ի�","Lady Dialla"}}}
        },
        [����״̬("Travel to The Belly of the Beast")] = {--����֮��:�� 1 ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Belly of the Beast Level 1"}},"The Crystal Veins"}  
        },
        [����״̬("Destroy the Beast within")] = {--�������֮��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Belly of the Beast Level 2"},{"��","The Bowels of the Beast"},{"ɱ��","Piety, the Abomination"}},"The Crystal Veins"}
        },
        [����״̬("Kill Piety")] = {  --��С��ͼ����   
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
        [����״̬("Kill Doedre")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Doedre Darktongue"}}}
        },
        [����״̬("Kill Maligaro")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Maligaro Darktongue"}}}
        },
        [����״̬("Kill Shavronne")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Shavronne of Umbra"}}}
        },
        [����״̬("Kill Shavronne to access the Black Core")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Shavronne of Umbra"}}}
        },
        [����״̬("Enter the Black Core")] = {--����������--Malachai, The Nightmare����������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Piety"},{"ɱ������","The Black Hear"}}}
        },
        [����״̬("Kill Malachai")] = {  --�����������������Խ���������     -- �����Ҫɱ�����ֲ��� ����״̬������ı�
            --[��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��λ��","Malachai, The Nightmare"}}}
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Black Hear"},{"ɱ��","Malachai, The Nightmare"}}}
        },
        [����״̬("Kill Malachai's guardians to access the Black Core")] = { --����û������ȶ�   --ɱ���� �򿪺������
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Piety"}}}
           -- ��(��_����������)
        },
    }),

   ����("Corpus Malachus",{
        [����״̬("Deliver the organ to Piety")] = { 
            [��(ͨ������_ɱ�������ͼ����)] ={"�Ի�","Piety"}
        },
   }),

    --3.0�������� -----------------------------------------------
   ����("Return to Oriath",{
        [����״̬("Travel to The Ascent")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Access the Ascent from the eastern side of Highgate")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Climb the Ascent to find the portal back to Oriath")] = {
            [��(ͨ������_ɱ�������ͼ����)] = { {{"ɱ��","Lever"}}}
        },
        [����״̬("Activate the Resonator and travel back to Oriath")] = {
            [��(ͨ������_ɱ�������ͼ����)] = { {{"��","Lever"}}}
        },
        [����״̬("Enter the portal to Oriath")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Oriath Portal"}}}
        },
        [����״̬("Escape the Slave Pens")] = {
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Overseer Krow"}}}
        },
        [����״̬("Enter Overseer's Tower")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Kill Overseer Krow to access town")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Overseer Krow"}}}
        },
        [����״̬("Talk to Lani for a reward")] = {  
            [��(ͨ������_�ύ����)]= {"Lani","Overseer Reward",1},
        },
    }),

    ����("The Key to Freedom",{
        [����״̬("Kill Justicar Casticus")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Justicar Casticus"}}}
        },
        [����״̬("Climb the Ascent to find the portal back to Oriath")] = {
            --��(ͨ������_ɱ�������ͼ����)--] = { {{"�Ի�","Lady Dialla"}},��}
            ͨ��������_ȫͼɱ��
        },
        [����״̬("Activate the Resonator and travel back to Oriath")] = {
            ��(ͨ������_ɱ�������ͼ����)--] = { {{"ɱ��","Oriath Portal"}}}
        },
        [����״̬("Enter the portal to Oriath")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Oriath Portal"}}}
        },
        [����״̬("Enter Overseer's Tower")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Lani for your reward")] = {  
            [��(ͨ������_�ύ����)]= {"Lani","Casticus Reward",1},
        },
    }),

    ����("In Service to Science",{
        [����״̬("Return the Miasmeter to Vilenta")] = {
            [��(ͨ������_�ύ����)]= {"Vilenta","Miasmeter Reward",1},
        },
        [����״̬("Talk to Vilenta for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Vilenta","Miasmeter Reward",1},
        },
    }),

    ����("Death to Purity",{
        [����״̬("Travel to The Control Blocks")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Take the Eyes of Zeal")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Eyes of Zeal"}}}
        },
        [����״̬("Gain access to the Templar Courts")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Justicar Casticus"}}}
        },
        [����״̬("Activate the Resonator and travel back to Oriath")] = {
            ��(ͨ������_ɱ�������ͼ����)--] = { {{"ɱ��","Oriath Portal"}}}
        },
        [����״̬("Enter the portal to Oriath")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Oriath Portal"}}}
        },
        [����״̬("Use the Eyes of Zeal to access the Templar Courts")] = {  
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Chamber of Innocence")] = {  
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find High Templar Avarius and kill him")] = {  
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Sanctum of Innocence"},{"ɱ��","Innocence, God-Emperor of Eternity"}}}
        },
        [����״̬("Kill High Templar Avarius")] = {  
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Sanctum of Innocence"},{"ɱ��","Innocence, God-Emperor of Eternity"}}}
        },
        [����״̬("Talk to Sin")] = {  
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Sanctum of Innocence"},{"�Ի�","Sin"}}}
        },
        [����״̬("Talk to Lani for your reward")] = {  
            [��(ͨ������_�ύ����)]= {"Lani","Avarius Reward",2},
        },
    }),

    ����("The Ravenous God",{
        [����״̬("Travel to The Chamber of Innocence")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Cathedral Rooftop")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Search the Ossuary for the Sign of Purity")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Sign of Purity"}},"The Ossuary"}
        },
        [����״̬("Use the Sign of Purity to defeat Kitava")] = {       --������Kitava's Torments���� {"�������","Kitava's Torments"},
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Cathedral Apex"},{"��","Cradle of Purity"}}}
        },
        [����״̬("Kill Kitava")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Cathedral Apex"},{"�򿪸���","Cradle of Purity"},{"ɱ��","Kitava, the Insatiable"}}}
        },
        [����״̬("Talk to Sin")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Take the ship back to Wraeclast")] = {
            [��(ͨ������_�Ի�NPC)] = {"Lilly Roth","Sail to Wraeclast"}
        },
    }),
    
    ����("Kitava's Torments",{
        [����״̬("Travel to the Reliquary")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find Kitava's Torments")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Tukohama's Tooth"}}}
        },
        [����״̬("Find the rest of Kitava's Torments")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Hinekor's Hair"}}}
        },
        [����״̬("Find the last of Kitava's Torments")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Valako's Jaw"}}}
        },
        [����״̬("Deliver Kitava's Torments to Lani")] = {
            [��(ͨ������_�ύ����)]= {"Lani","Torments Reward",1},
        },
        [����״̬("Talk to Lani for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Lani","Torments Reward",1},
        },
    }),

    ����("The King's Feast",{
        [����״̬("Talk to Bannon in the Chamber of Innocence")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Bannon"}}}
        },
        [����״̬("Talk to Bannon in town for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Bannon","Utula Reward",1},
        },
        [����״̬("Kill Utula")] = {        --������������´�ע�⿴��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Utula"}}}
        },
    }),



    -------����������--------------------

    ����("Bestel's Epic",{
        [����״̬("Find Bestel's Manuscript at the Tidal Island")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Bestel's Manuscript"}}}
        },
        [����״̬("Deliver the Manuscript to Bestel")] = {
           [��(ͨ������_�ύ����)]= {"Bestel","Bestel's Epic Reward",1},
        },
        [����״̬("Talk to Li")] = {
           [��(ͨ������_�ύ����)]= {"Bestel","Bestel's Epic Reward",1},
        },
    }),
    
    ����("The Father of War",{
        [����״̬("Search the area for whoever has the missing eye")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Eye of Conquest"}}}
        },
        [����״̬("Use the eye to access the Karui Fortress")] = {
            [��(ͨ������_ɱ�������ͼ����) ] = {{{"��","Fortress Gate"}}}
        },
        [����״̬("Travel to The Mub Flats")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Access the Karui Fortress")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Karui Fortress"}}}
        },
        [����״̬("Find the exit to the Karui Fortress")] = {
            [��(ͨ������_ɱ�������ͼ����)] =    {{{"ɱ������", "Tukohama's Keep"},{"ɱ��", "Tukohama, karui God of War"}}}
        },
        [����״̬("Defeat Tukohama to unlock the exit")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������", "Tukohama's Keep"},{"ɱ��", "Tukohama, karui God of War"}}}
        },
        [����״̬("Talk to Tarkleigh for a reward")] = {
            [��(ͨ������_�ύ����)]= {"Tarkleigh","Tukohama Reward",1},
        }
    }),

    ��������("Essence of Umbra",{
        [����״̬("Talk to Sin")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Kill Shavronne")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�������","The Father of War"},{"ɱ������","Prison Rooftop"},{"ɱ��","Shavronne the Returned"}},"Shavronne's Tower"}
        },
--        [����״̬("Travel to Axiom Prison")] = {
--            [��(ͨ������_ɱ�������ͼ����)] = {{{"�������","The Father of War"},{"ɱ��","Fortress Gate"},{"�������","The Father of War"}},"The Mud Flats"}
--        },
        [����״̬("Kill Shavronne and Brutus")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�������","The Father of War"},{"ɱ������","Prison Rooftop"},{"ɱ��","Shavronne the Returned"}},"��ǰ��ͼ"}
        },
        [����״̬("Talk to Tarkleigh for your reward")] = {
             [��(ͨ������_�ύ����)]= {"Tarkleigh","Shavronne Reward",1},
        },
    }),

   ����("The Puppet Mistress",{
        [����״̬("Defeat the Puppet Mistress")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Spawning Ground"},{"ɱ��","Ryslatha, the Puppet Mistress"}}}
        },
        [����״̬("Talk to Tarkleigh for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Tarkleigh","Puppet Mistress Reward",1},
        },
    }),

    ��������("The Brine King",{
        [����״̬("Search the Mud Flats for Nessa")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Nessa"}}}
        },
        [����״̬("Travel through Prisoner's Gate to the Ship Graveyard")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","The Black Flag"}}}
        },
        [����״̬("Use the Black Flag at the Beacon to summon the Black Crest")] = {    --ɱ�����Ӹ��������¸�����״̬
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","���ƶ�����"}}}
        },
        [����״̬("Push the fuel carts into position to refuel the Beacon")] = {    --����������
            ��(��_����������)
        },
        [����״̬("Travel to The Beacon")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Light the Beacon and throw the Black Flag into the flames")] = { --ɱ���򿪻��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Ignition Switch"}}}
        },
        [����״̬("Talk to Weylam Roth at the Beacon")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Weylam Roth"}}}
        },
        [����״̬("Board the Black Crest to sail to the Brine King's Reef")] = { 
            [��(ͨ������_�Ի�NPC)] = {"Weylam Roth","Sail to the Brine King's Reef"}
        },
        [����״̬("Search the Brine King's Reef for Nessa")] = { 
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Brine King's Throne"},{"ɱ��","Tsoagoth, The Brine King"}}}
        },
        [����״̬("Defeat the Brine King")] = { 
             [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Brine King's Throne"},{"ɱ��","Tsoagoth, The Brine King"}}}
        },
        [����״̬("The exit to Act 7 is now open")] = {
             [��(ͨ������_�Ի�NPC)]= {"Weylam Roth now","Sail to Act 7"},
        },
    }),

    ����("Fallen from Grace",{
        [����״̬("Clear the Twilight Strand")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ȫͼɱ","Fallen from Grace"}}}
        },
        [����״̬("Talk to Lilly for your reward")] = {
           [��(ͨ������_�ύ����)]= {"Lilly Roth","Twilight Strand Reward",1},
        },
    }),



    ����("The Cloven One",{
        [����״̬("Defeat Abberath")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Valley of the Fire Drinker"},{"ɱ��","Abberath, the Cloven One"}}}
        },
        [����״̬("Talk to Bestel for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Bestel","Aberrath Reward",1},
        },
    }),
    --------------------������---------------------------------
    ����("Essence of the Artist",{
        [����״̬("Talk to Sin")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Talk to Helena to find out how to reach Maligaro")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Helena"}}}
        },
        [����״̬("Find Maligaro's Map")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Maligaro's Map"}}}
        },
        [����״̬("Travel to The Chamber of Sins")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Crypt")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find Maligaro")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Chamber of Sins Level 1"},{"��","Map Device"}},"The Bridge Encampment"}
        },
        [����״̬("Use Maligaro's Map in his Map Device")] = { --�������װ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"����װ��","Maligaro's Map"}}}
        },
        [����״̬("Enter Maligaro's Sanctum")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Maligaro's Workshop"},{"��","Black Venom"}}}
        },
        [����״̬("Find Maligaro and kill him")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Maligaro's Workshop"},{"��","Black Venom"}}}
        },
        [����״̬("Kill Maligaro")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Maligaro's Workshop"},{"��","Black Venom"}},"Maligaro's Sanctum"}
        },
        [����״̬("Talk to Helena for your reward")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Bridge Encampment"},{"�Ի�","Helena"}},"The Bridge Encampment"}
        },
        [����״̬("Travel to Maligaro's Sanctum")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"����װ��","Maligaro's Map"},{"ɱ����ͼ","Maligaro's Sanctum"}},"The Chamber of Sins Level 1"}
        },
        [�ύ(ͨ������_�ύ����)]= {"Helena","Maligaro Reward",1},
    }),

    ����("Web of Secrets",{
        [����״̬("Bring the Black Venom to Silk")] = {
            [��(ͨ������_�ύ����)]= {"Silk","Black Death Reward",1},
        },
        [����״̬("Talk to Silk for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Silk","Black Death Reward",1},
        },
    }),

    ����("The Master of a Million Faces",{
        [����״̬("Find a way info the Den")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Use the Obsidian Key to access the Den")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Secret Passage"}},"The Chamber of Sins Level 2"}
        },
        [����״̬("Find the old Forest Encampment")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Fortress Encampment"},{"ɱ��","Greust, Lord of the Forest"}}}
        },
        [����״̬("Kill Greust")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Fortress Encampment"},{"ɱ��","Greust, Lord of the Forest"}}}
        },
        [����״̬("Talk to Eramir for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Eramir","Ralakesh Reward",1},
        },
        [�ύ(ͨ������_�ύ����)]= {"Eramir","Ralakesh Reward",1},
    }),
    
    ����("In Memory of Greust",{
        [����״̬("Take Greust's Necklace from Helena")] = {
            [��(ͨ������_�ύ����)]= {"Helena","Take Greust's Necklace",1},
        },
        [����״̬("Ask Helena about the Azmeri Shrine")] = {
            [��(ͨ������_�ύ����)]= {"Helena","Take Greust's Necklace",1},
        },
        [����״̬("Take Greust's Necklace to the shrine in the Northern Forest")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Azmeri Shirine"}}}
        },
        [����״̬("Place Greust's Necklace on the Azmeri shrine")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Azmeri Shirine"}}}
        },
        [����״̬("Travel to The NorThern Forest")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Talk to Helena for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Helena","Greust's Necklace Reward",1},
        },

        [�ύ(ͨ������_�ύ����)]= {"Helena","Greust's Necklace Reward",1},
    }),

    ����("The Mother of Spiders",{
        [����״̬("Find Arakaali's temple and save Silk")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","The Temple of Decay Level 1"},{"�Ի�","Yeena"}},"The Vaal City"}
        },
        [����״̬("Enter Arakaali's temple and save Silk")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Temple of Decay Level 2"}
        },
        [����״̬("Travel to The Temple of Decay")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{}},"The Temple of Decay Level 2"}
        },
        [����״̬("Find Silk and Arakaali")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Arakaali's Web"},{"ɱ��","Arakaali, Spinner of Shadows"}},"The Temple of Decay Level 2"}
        },
        [����״̬("Kill Arakaali")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Arakaali's Web"},{"ɱ��","Arakaali, Spinner of Shadows"}},"The Temple of Decay Level 2"}
        },
        [����״̬("The exit to Act 8 is now open")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Sarn Ramparts"}},"The Bridge Encampment"}
        },
    }),

    ����("Lighting the Way",{
        [����״̬("Search the Dread Thicket for Fireflies")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Firefly"}}}
        },
        [����״̬("Search the Dread Thicket for the remaining Fireflies")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Firefly"}}}
        },
        [����״̬("Deliver the Fireflies to Yeena at Arakaali's temple")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Yeena"}},"The Vaal City"}
        },
    }),

    ����("Kishara's Star",{
        [����״̬("Deliver Kishara's Star to Weylam")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Weylam Roth"}}}
        },
        [����״̬("Talk to Weylam for your reward")] = {
            [��(ͨ������_�ύ����)]= {"Weylam Roth","Kishara's Star Reward",1},
        },
    }),

    ����("The Silver Locket",{
        [����״̬("Find Weylam's Silver Locket")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Silver Locket"}}}
        },
        [����״̬("Deliver the Silver Locket to Weylam")] = {
            [��(ͨ������_�ύ����)] = {"Weylam Roth","Silver Locket Reward",1}
        },
        [�ύ(ͨ������_�ύ����)] = {"Weylam Roth","Silver Locket Reward",1}
    }),



    -------------------------------�ڰ���----------------------------
    ����("Essence of the Hag",{
        [����״̬("Meet Sin at the Sarn Encampment")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Find and kill Doedre")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Doedre"}},"The Toxic Conduits"}
        },
        [����״̬("Travel to The Toxic Conduits")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Kill Doedre")] = {       --������ ��һֱɱ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Cauldron"},{"ɱ��","Doedre the Vile"}}}
        },
        [����״̬("Talk to Hargan for your reward")] = {     
             [��(ͨ������_�ύ����)] = {"Hargan","Doedre Reward",1}
        },
        [�ύ(ͨ������_�ύ����)] = {"Hargan","Doedre Reward",1}
    }),

    ����("The Wings of Vastiri",{
        [����״̬("Travel to The Bath House")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the Wings of Vastiri")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Hector Titucius, Eternal Servan"}}}
        },
        [����״̬("Kill Hector Titucius")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ��","Hector Titucius, Eternal Servant"}}}
        },
        [����״̬("Deliver the Wings of Vastiri to Hargan")] = {
            [��(ͨ������_�ύ����)] = {"Hargan","Wings of Vastiri Reward",1}
        },
        [�ύ(ͨ������_�ύ����)] = {"Hargan","Wings of Vastiri Reward",1}
    }),

    ����("Lunar Eclipse",{
        [����״̬("Talk to Maramoa")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Maramoa"}}}
        },
        [����״̬("Travel to The Lunaris Temple")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Travel to The Harbour Bridge")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the Moon Orb")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Portal"},{"��","Moon Orb"}},"The Lunaris Temple Level 2"}
        },
        [����״̬("Kill Dusk")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Portal"},{"��","Moon Orb"}},"The Lunaris Temple Level 2"}
        },
        [����״̬("Find the Sun Orb")] = {
            --[��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Solaris Temple Level 2"},{"��","Sun Orb"}},"The Sarn Encampment"}
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Sun Orb"}},"The Solaris Temple Level 2"}
        },
        [����״̬("Take the Moon Orb to the Harbour Bridge")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Sky Shrine"},{"��","Statue of The Sisters"}}}
        },
        [����״̬("Kill Solaris and Lunaris")] = { --Solaris,Eternal Sun
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Sky Shrine"},{"ɱ��","Lunaris, Eternal Moon"}}}
        },
        [����״̬("Take the Moon Orb")] = { 
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Portal"},{"��","Moon Orb"}},"The Lunaris Temple Level 2"}
        },
        [����״̬("The exit to Act 9 is now open")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ����ͼ","The Blood Aqueduct"}},"The Sarn Encampment"}
        },
    }),

    ����("Love is Dead",{  
        [����״̬("Travel to The Quay")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
        [����״̬("Find the Ankh of Eternity")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Ankh of Eternity"}}}
        },
        [����״̬("Give her the Ankh")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Arena"},{"�Ի�","Clarissa"}}}
        },
        [����״̬("Talk to Clarissa")] = {
            [��(ͨ������_�ύ����)] = {"Clarissa","Tolman Reward",1}
        },
    }),

    ����("The Gemling Legion",{  
        [����״̬("Talk to Maramoa for your reward")] = {
            [��(ͨ������_�ύ����)] = {"Maramoa","Gemling Legion Reward",1}
        },
        [����״̬("Travel to The Grain Gate")] = {
            ��(ͨ������_ɱ�������ͼ����)
        },
    }),

    ����("Reflection of Terror",{  
        [����״̬("Kill Yugul")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","The Pools of Terror"},{"ɱ��","Yugul, Reflection of Terror"}}}
        },
        [����״̬("Talk to Hargan for your reward")] = {
            [��(ͨ������_�ύ����)] = {"Hargan","Yugul Reward",1}
        },
    }),

-----------------�ھ�������---------------------
    ����("Recurring Nightmare",{  
        [����״̬("Meet Sin in Highgate")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Find the Basilisk Acid")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Basilisk Acid"}}}
        },
        [����״̬("Find the Trarthan Powder")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"��","Trarthan Powder"}}}
        },
        [����״̬("Deliver the Trarthan Powder to Sin")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Meet Sin at the Quarry")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Meet Sin at the Black Core")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Defeat the spirit of Doedre")] = {
            [��(ͨ������_ɱ�������ͼ�����ظ�)] = {{{"ɱ������","Doedre's Despair"},{"���´�","The Black Heart"}}}
        },
        [����״̬("Defeat the spirit of Shavronne")] = {
            [��(ͨ������_ɱ�������ͼ�����ظ�)] = {{{"ɱ������","Shavronne's Sorrow"},{"���´�","The Black Heart"}}}
        },
        [����״̬("Defeat the spirit of Maligaro")] = {
            [��(ͨ������_ɱ�������ͼ�����ظ�)] = {{{"ɱ������","Maligaro's Misery"},{"���´�","The Black Heart"}}}
        },
        [����״̬("Talk to Sin")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Sin"}}}
        },
        [����״̬("Kill the Depraved Trinity")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"���´�","The Black Heart"}}}
        },
        [����״̬("Talk to Lilly")] = {  --ת����ʮ��
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Lilly Roth"}}}
        },

    }),
        
--    ����("The Ruler of Highgate",{  
--        [����״̬("Find Oyun and save her from Kira")] = {
--            ��(ͨ������_ɱ�������ͼ����)
--        },
--    }),

---------------------��ʮ��------------------
    ����("Safe Passage",{  
        [����״̬("Find Bannon on the Cathedral Rooftop and save him")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Cathedral Apex"},{"ɱ��","Plaguewing"}}}
        },
        [����״̬("Fight off Kitava's cultists to rescue Bannon")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Cathedral Apex"},{"ɱ��","Plaguewing"}}}
        },
        [����״̬("Defeat Plaguewing to rescue Bannon")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Cathedral Apex"},{"ɱ��","Plaguewing"}}}
        },
        [����״̬("Talk to Bannon")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Cathedral Apex"},{"�Ի�","Bannon"}}}
        },
        [����״̬("Meet Bannon back at the docks")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"�Ի�","Bannon"}}}
        },
        [����״̬("Talk to Lani for your reward")] = {
            [��(ͨ������_�ύ����)] = {"Lani","Bannon Reward",1}
        },
    }),

    ����("Death and Rebirth",{  
        [����״̬("Find the Staff of Purity")] = {
            [��(ͨ������_ɱ�������ͼ����)] = {{{"ɱ������","Cathedral Apex"},{"ɱ��","Plaguewing"}}}
        },
        [����״̬("Talk to Lani for your reward")] = {
            [��(ͨ������_�ύ����)] = {"Lani","Bannon Reward",1}
        },
    }),
}



���������()
����������(���е�����)

