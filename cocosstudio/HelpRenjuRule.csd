<GameProjectFile>
  <PropertyGroup Type="Node" Name="HelpRenjuRule" ID="a878ca95-2789-4286-998b-0dbcb020c3b8" Version="2.1.5.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000">
        <Timeline ActionTag="1435599715" FrameType="PositionFrame" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="1435599715" FrameType="ScaleFrame" Property="Scale">
          <PointFrame FrameIndex="0" X="0.1000" Y="0.1000" />
          <PointFrame FrameIndex="20" X="1.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="1435599715" FrameType="RotationSkewFrame" Property="RotationSkew">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="-189238168" FrameType="PositionFrame" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="9.9990" />
          <PointFrame FrameIndex="20" X="0.0000" Y="120.0000" />
        </Timeline>
        <Timeline ActionTag="-189238168" FrameType="ScaleFrame" Property="Scale">
          <PointFrame FrameIndex="0" X="0.1000" Y="0.1000" />
          <PointFrame FrameIndex="20" X="1.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="-189238168" FrameType="RotationSkewFrame" Property="RotationSkew">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="657637232" FrameType="PositionFrame" Property="Position">
          <PointFrame FrameIndex="0" X="1.0000" Y="0.9999" />
          <PointFrame FrameIndex="20" X="3.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="657637232" FrameType="ScaleFrame" Property="Scale">
          <PointFrame FrameIndex="0" X="0.1000" Y="0.1000" />
          <PointFrame FrameIndex="20" X="1.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="657637232" FrameType="RotationSkewFrame" Property="RotationSkew">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="-1536274726" FrameType="PositionFrame" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="-9.0004" />
          <PointFrame FrameIndex="20" X="0.0000" Y="-122.0000" />
        </Timeline>
        <Timeline ActionTag="-1536274726" FrameType="ScaleFrame" Property="Scale">
          <PointFrame FrameIndex="0" X="0.0250" Y="0.0250" />
          <PointFrame FrameIndex="20" X="0.2500" Y="0.2500" />
        </Timeline>
        <Timeline ActionTag="-1536274726" FrameType="RotationSkewFrame" Property="RotationSkew">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000" />
        </Timeline>
      </Animation>
      <ObjectData Name="Node" FrameEvent="" Tag="42" ctype="SingleNodeObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="0.0000" Y="0.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="ProjectNode_1" ActionTag="1435599715" FrameEvent="" Tag="51" IconVisible="True" ObjectIndex="1" ctype="ProjectNodeObjectData">
            <Position X="0.0000" Y="0.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="0.0000" Y="0.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Fence.csd" />
          </NodeObjectData>
          <NodeObjectData Name="Text_1" ActionTag="-189238168" FrameEvent="" Tag="62" FontSize="24" LabelText="렌주(Renju)룰" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ObjectIndex="1" ctype="TextObjectData">
            <Position X="0.0000" Y="120.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="160" G="42" B="0" />
            <Size X="145.0000" Y="24.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
          </NodeObjectData>
          <NodeObjectData Name="Text_2" ActionTag="657637232" FrameEvent="" Tag="64" FontSize="18" LabelText="Renju룰 항목에 체크하고 게임을 시작하면 &#xA;렌주(Renju)룰이 적용됩니다.&#xA;기존 오목은 먼저 두는 흑이 무조건 유리하&#xA;기 때문에 렌주룰에서는 흑에게만 3-3(쌍삼)&#xA;, 4-4(쌍사), 장목(6목이상) 을 둘 수 없도록 &#xA;제한을 둡니다.&#xA;렌주룰을 해제하면 흑과 백에 상관없이&#xA;사용자가 정한 규칙을 적용시킬 수 있습니다.&#xA;" ObjectIndex="2" ctype="TextObjectData">
            <Position X="3.0000" Y="1.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="32" G="32" B="32" />
            <Size X="360.0000" Y="162.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
          </NodeObjectData>
          <NodeObjectData Name="btn_close" ActionTag="-1536274726" FrameEvent="" Tag="82" TouchEnable="True" FontSize="72" ButtonText="닫기" Scale9Width="479" Scale9Height="132" ObjectIndex="1" ctype="ButtonObjectData">
            <Position X="0.0000" Y="-122.0000" />
            <Scale ScaleX="0.2500" ScaleY="0.2500" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="479.0000" Y="132.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="255" G="254" B="187" />
            <DisabledFileData Type="Normal" Path="Resources/button_sel.png" />
            <PressedFileData Type="Normal" Path="Resources/button_sel.png" />
            <NormalFileData Type="Normal" Path="Resources/button.png" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>