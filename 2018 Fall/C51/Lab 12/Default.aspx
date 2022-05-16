<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h1 style="text-align: center">Welcome to the Pizza Shop</h1>
        </div>
        <asp:Image ID="Image2" runat="server" Height="402px" ImageUrl="https://proxy.duckduckgo.com/iu/?u=https%3A%2F%2Fblog.oxforddictionaries.com%2Fwp-content%2Fuploads%2Fpizza.jpg&amp;f=1" style="text-align: center" Width="1593px" />
        <p>
            &nbsp;</p>
        <p>
            Choose the size of your pizza:</p>
        <asp:RadioButtonList ID="RadioButtonList3" runat="server" OnSelectedIndexChanged="RadioButtonList3_SelectedIndexChanged">
            <asp:ListItem Value="7.50">Personal - $7.50</asp:ListItem>
            <asp:ListItem Value="12.00">Medium - $12.00</asp:ListItem>
            <asp:ListItem Value="15.00">Large - $15.00</asp:ListItem>
            <asp:ListItem Value="18.00">Jumbo - $18.00</asp:ListItem>
        </asp:RadioButtonList>
        <br />
        Chooose the toppings for your pizza:<br />
        <asp:CheckBoxList ID="CheckBoxList1" runat="server" OnSelectedIndexChanged="CheckBoxList1_SelectedIndexChanged">
            <asp:ListItem Value="0.50">Mushroom - $0.50</asp:ListItem>
            <asp:ListItem Value="0.70">Pepperoni - $0.70</asp:ListItem>
            <asp:ListItem Value="1.05">Chicken - $1.05</asp:ListItem>
        </asp:CheckBoxList>
        <br />
        <br />
        <br />
        <asp:TextBox ID="TextBox1" runat="server" Height="19px" OnTextChanged="TextBox1_TextChanged" ReadOnly="True" style="margin-bottom: 2px"></asp:TextBox>
&nbsp;Subtotal<p>
            <asp:TextBox ID="TextBox2" runat="server" OnTextChanged="TextBox2_TextChanged" ReadOnly="True"></asp:TextBox>
&nbsp;Tax</p>
        <p>
            <asp:TextBox ID="TextBox3" runat="server" OnTextChanged="TextBox3_TextChanged" ReadOnly="True"></asp:TextBox>
&nbsp;Total</p>
        <p>
            <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="Finish" />
        </p>
    </form>
</body>
</html>
