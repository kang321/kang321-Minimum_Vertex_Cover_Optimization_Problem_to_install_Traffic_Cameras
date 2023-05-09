#!/usr/bin/env python3
import sys
import re
import numpy
dictt = {}

# YOUR CODE GOES HERE


def main():
    # YOUR MAIN CODE GOES HERE

    # sample code to read from stdin.
    # make sure to remove all spurious print statements as required
    # by the assignment


    # function to find intersection of line-segments
    def intersect(p1, p2, p3, p4):
        xnum = ((p1[0] * p2[1] - p1[1] * p2[0]) * (p3[0] - p4[0]) - (p1[0] - p2[0]) * (p3[0] * p4[1] - p3[1] * p4[0]))
        xden = ((p1[0] - p2[0]) * (p3[1] - p4[1]) - (p1[1] - p2[1]) * (p3[0] - p4[0]))
        if xden == 0:
            return
        else:
            xcoor = xnum / xden
            xcoor = round(xcoor, 2)
        ynum = (p1[0] * p2[1] - p1[1] * p2[0]) * (p3[1] - p4[1]) - (p1[1] - p2[1]) * (p3[0] * p4[1] - p3[1] * p4[0])
        yden = (p1[0] - p2[0]) * (p3[1] - p4[1]) - (p1[1] - p2[1]) * (p3[0] - p4[0])
        ycoor = ynum / yden
        ycoor = round(ycoor, 2)
        if min(p1[0], p2[0]) <= xcoor <= max(p1[0], p2[0]) and min(p1[1], p2[1]) <= ycoor <= max(p1[1], p2[1]):
            if min(p3[0], p4[0]) <= xcoor <= max(p3[0], p4[0]) and min(p3[1], p4[1]) <= ycoor <= max(p3[1], p4[1]):
                p5 = [xcoor, ycoor]
                return p5

    # to find edges:
    def edges(p1_p2_p5_ll, vertices_dict):
        # to calculate edges>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        indexx = []
        f_list = []

        # print("p1_p2_p5_ll", p1_p2_p5_ll)

        for m in range(0, len(p1_p2_p5_ll)):
            set_of_p5 = []
            for n in range(m + 1, len(p1_p2_p5_ll)):
                if (p1_p2_p5_ll[m][0] == p1_p2_p5_ll[n][0]) and (p1_p2_p5_ll[m][1] == p1_p2_p5_ll[n][1]):
                    set_of_p5.append(p1_p2_p5_ll[n][2])
                    # print(set_of_p5)
                    indexx.append(m)
                    indexx.append(n)

            list_of_points_p1_p2_p5_so_on = [p1_p2_p5_ll[m][0], p1_p2_p5_ll[m][1], p1_p2_p5_ll[m][2]]

            # print("'''",list_of_points_p1_p2_p5_so_on)
            # print("int_points", set_of_p5)
            list_of_points_p1_p2_p5_so_on.extend(set_of_p5)
            # print("extended",list_of_points_p1_p2_p5_so_on)
            f_list.append(list_of_points_p1_p2_p5_so_on)

        # removing dupes
        # print("indexbefore",indexx)
        index = list(dict.fromkeys(indexx))  # remove repeatations
        # print("indexafter", index)  # 1 3 5 7

        index.sort(reverse=True)
        # print("index", index)  # 7 5 3 1

        f1_list = f_list.copy()
        # print("f_list", f_list)
        for h in index:
            f1_list.pop(h)
        # print("f1_list", len(f1_list), f1_list) #list of coordinates of edges

        # print("combination into p1p5 p2p5 points needs to be done",f_list)
        edges1 = []  # list of single edges

        for p in range(len(f1_list)):
            edges = []
            point1 = f1_list[p][0]
            point2 = f1_list[p][1]
            point5 = f1_list[p][2]
            edges.append(point1)
            edges.append(point5)
            edges1.append(edges)
            edges = []
            edges.append(point2)
            edges.append(point5)
            edges1.append(edges)
        # print("list of single intersection edges are:",edges1)
        # print("single", edges1)
        # print("number of single intersection edges are: ",len(edges1))

        #######################################################################################################
        # print("f_list", f_list)
        # print("f1_list", f1_list)
        index.reverse()  # 1 3 5 7
        ff_list = []
        for hk in index:
            ff_list.append(f_list[hk])
        # print(index)
        # print("ff_list", ff_list)
        idx = []
        # 1254
        # 3459
        # 6789
        for i in range(len(ff_list) - 1):
            for j in range(i + 1, len(ff_list)):
                if ff_list[i][0] == ff_list[j][0]:
                    idx.append(j)

        idx = list(dict.fromkeys(idx))
        idx.reverse()
        for wq in idx:
            del ff_list[wq]
        # print("ff_list", ff_list)  # list of points with multiple intersection (p1,p2,p5,p6,p7...)

        tcr2 = []
        tcrr = []
        tcr3 = []
        for val in range(len(ff_list)):
            tcr = []
            ycr = []
            xcr = []
            if ff_list[val][0][0] == ff_list[val][1][0]:
                for uu in range(len(ff_list[val])):
                    ycr.append(ff_list[val][uu][1])
                    ycr.sort()
                for gg in ycr:
                    for uv in range(len(ff_list[val])):
                        if gg == ff_list[val][uv][1]:
                            tcr.append(ff_list[val][uv])

                tcr2.append(tcr)
            else:

                for uuu in range(len(ff_list[val])):
                    xcr.append(ff_list[val][uuu][0])
                    xcr.sort()

                for ggg in xcr:
                    for uvv in range(len(ff_list[val])):
                        if ggg == ff_list[val][uvv][0]:
                            tcr.append(ff_list[val][uvv])

                tcr3.append(tcr)

        tcr3.extend(tcr2)
        # print("tcr2",tcr2)
        # print("tcr",tcr)
        # print(tcr3, "tcr3")
        edge_mul = []
        for i in range(len(tcr3)):
            for d in range(len(tcr3[i]) - 1):
                edge_ss = []
                # print(a[i][d],a[i][d+1])
                edge_ss.append(tcr3[i][d])
                edge_ss.append(tcr3[i][d + 1])
                edge_mul.append(edge_ss)
        # print("edge1",edges1)
        # print("edge_mul",edge_mul,len(edge_mul))
        edges1.extend(edge_mul)

        for key, vals in vertices_dict.items():
            for ik in range(len(edges1)):
                for jk in range(len(edges1[ik])):
                    if edges1[ik][jk] == vals:
                        edges1[ik][jk] = key
        # removing repeatations of edges:::::::::::::::::::::::::
        indx = []
        for ko in range(len(edges1) - 1):
            if edges1[ko] == edges1[ko + 1]:
                indx.append(ko)
                indx.append(ko + 1)
        indx.reverse()
        for id in indx:
            del edges1[id]

        # formating the dictionary according to assignment
        for ky, ve in vertices_dict.items():
            vertices_dict[ky] = tuple(ve)
            # v=(tuple(v))
        print("V = ", vertices_dict)

        # formatting edge in terms of assignment
        set1 = set()
        print("\nE = {")
        for edge in edges1:
            if edge != edges1[-1]:
                print(' <' +str(edge[0]) + "," + str(edge[1]) + ">,")
            else:
                print(' <' +str(edge[0]) + "," + str(edge[1]) + ">")    
                
        print("}")        
        #     y = x.replace("]", ">")
       #     set1.add(y)
        # print("E : ", set1)

    def gg():
        vertices_dupefree = []
        vertices = []
        p1_p2_p5_ll = []
        # print("dictt", dictt)

        points_collection = list(dictt.values())
        for street in range(len(points_collection) - 1):
            for x in range(0, len(points_collection[street]) - 1):
                p1 = points_collection[street][x]
                p2 = points_collection[street][x + 1]
                for street2 in range(street + 1, len(points_collection)):
                    for y in range(len(points_collection[street2]) - 1):
                        p3 = points_collection[street2][y]
                        p4 = points_collection[street2][y + 1]
                        p5 = intersect(p1, p2, p3, p4)

                        if p5 != None:
                            p1_p2_p5 = []
                            p1_p2_p5.append(p1)
                            p1_p2_p5.append(p2)
                            p1_p2_p5.append(p5)
                            p1_p2_p5_ll.append(p1_p2_p5)

                            p1_p2_p5 = []
                            p1_p2_p5.append(p3)
                            p1_p2_p5.append(p4)
                            p1_p2_p5.append(p5)
                            p1_p2_p5_ll.append(p1_p2_p5)

                            vertices.append(p1)
                            vertices.append(p2)
                            vertices.append(p3)
                            vertices.append(p4)
                            vertices.append(p5)
                            # print("All intersection:", p1,p2,p3,p4,p5)
                            # a1 = [p1,p2,p3,p4,p5]
                            # print("all points with intersection",a1)
        vertices_dict = {}
        for x in vertices:
            if x not in vertices_dupefree:
                vertices_dupefree.append(x)
        # vertices_dupfree to dic with name of vertices
        for val in range(len(vertices_dupefree)):
            vertices_dict[val + 1] = vertices_dupefree[val]
        # print("the vertices are: ", vertices_dict)
        edges(p1_p2_p5_ll, vertices_dict)




    def add_fun():
        regex_street_name = '\".+\"'
        regex_coordinate_numbers = r'-?\d+'
        pattern = re.findall(regex_street_name, inst_list_raw.lower())
        pattern_num = re.findall(regex_coordinate_numbers, inst_list_raw)

        if pattern[0] in dictt.keys():
            print("Error: street currently exists")
            return

        # converting pattern_num str to int:
        pattern_num_1 = []
        for k in range(len(pattern_num)):
            # print"before", type(num_list[i]))
            pattern_num[k] = (int(pattern_num[k]))
            pattern_num_1.append(pattern_num[k])

        # p=numpy.array[pattern_num[0]]
        # creating numpy array to store coordinates with column 2 and row
        pattern_num_1 = numpy.array(pattern_num_1)
        pattern_num_1 = pattern_num_1.reshape(-1, 2)
        pattern_num_1 = pattern_num_1.tolist()
        # print(type(pattern_num))
        # assigning value to dictionary
        dictt[pattern[0]] = pattern_num_1
        # streetname.append(re.findall(pattern,a))

    def rm_fun():
        regex_street_name = '\".+\"'
        pattern = re.findall(regex_street_name, inst_list_raw.lower())
        if pattern[0] not in dictt.keys():

            print("Error: street not found, cant remove")

        else:
            del dictt[pattern[0]]
            # dictt.pop(pattern[0])
        return

    def mod_fun():
        regex_street_name = '\".+\"'
        regex_coordinate_numbers = r'-?\d+'
        pattern = re.findall(regex_street_name, inst_list_raw.lower())
        pattern_num = re.findall(regex_coordinate_numbers, inst_list_raw)

        if pattern[0] not in dictt.keys():
            print("Error: street not found")
            return

        # converting pattern_num str to int:
        pattern_num_1 = []
        for k in range(len(pattern_num)):
            # print"before", type(num_list[i]))
            pattern_num[k] = (int(pattern_num[k]))
            pattern_num_1.append(pattern_num[k])

        # p=numpy.array[pattern_num[0]]
        # creating numpy array to store coordinates with column 2 and row
        pattern_num_1 = numpy.array(pattern_num_1)
        pattern_num_1 = pattern_num_1.reshape(-1, 2)
        pattern_num_1 = pattern_num_1.tolist()
        # print(type(pattern_num))
        # assigning value to dictionary
        dictt[pattern[0]] = pattern_num_1
        # streetname.append(re.findall(pattern,a))


    while True:
        inst_list_raw = sys.stdin.readline()
        if inst_list_raw == "":
            break
        # print("read a line:", line)
        regex_add = '^add\s((\"[a-zA-Z]\")|(\"([a-zA-Z]+\s*){1,}\S\"))((\s\(-?\d+,-?\d+\)){2,})$'
        regex_mod = '^mod\s((\"[a-zA-Z]\")|(\"([a-zA-Z]+\s*){1,}\S\"))((\s\(-?\d+,-?\d+\)){2,})$'
        regex_rm = '^rm\s((\"[a-zA-Z]\")|(\"([a-zA-Z]+\s*){1,}\S\"))'
        regex_gg = '^gg$'


        if re.match(regex_add, inst_list_raw):
            # print("found match: Call function of add")
            add_fun()

        elif re.match(regex_mod, inst_list_raw):
            # print("found match: Call function of mod")
            mod_fun()

        elif re.match(regex_rm, inst_list_raw):
            # print("found match: call function of rm")
            rm_fun()

        elif re.match(regex_gg, inst_list_raw):
            # print("found match: call function of gg")
            gg()

        else:
            print("Error: Wrong instruction")

    # print("Finished reading input")
    # return exit code 0 on successful termination
    sys.exit(0)


if __name__ == "__main__":
    main()
